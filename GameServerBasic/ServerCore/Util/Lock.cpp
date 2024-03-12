#include "stdafx.h"
#include "Lock.h"

#ifdef _DEBUG
#define STERN_MODE
#endif

constexpr int INVALID_LINE = -1;

Lock::Lock(const wchar_t* name)
	: _lockId{ LockManager::GetInstance().GenerateId() },
	_name{ name },
	_lockingLine{ INVALID_LINE }
{	
}

const wchar_t* Lock::GetName() const
{
	return _name.c_str();
}

size_t Lock::GetLockId() const
{
	return _lockId;
}

lock_t& Lock::GetMutex()
{
	return _mutex;
}

size_t Lock::GetThreadId() const
{
	return _threadId;
}

void Lock::SetThreadId(size_t value)
{
	_threadId = value;
}

void Lock::ProcessLock(LPCWSTR fileName, int lineNo)
{
	_mutex.lock();

	_lockingFile = fileName;
	_lockingLine = lineNo;
}

void Lock::Unlock()
{
	_mutex.unlock();

	_lockingFile.clear();
	_lockingLine = INVALID_LINE;
}

LockSafeScope::LockSafeScope(Lock* lock, LPCWSTR fileName, int lineNo)
	: _lock{ lock }
{
	if (_lock == nullptr)
	{
		return;
	}

	// TODO : _shutdown ±¸Çö
	/*if (_shutdown)
	{
		return;
	}*/

	Lock* deadLock = LockManager::GetInstance().CheckDeadLock(_lock);
	if (deadLock != nullptr)
	{
#ifdef STERN_MODE
		//SErrLog(L"! [%s]lock and [%s]lock is dead detecting", deadLock->GetName(), lock->GetName());
#else
		std::lock(_lock->GetMutex(), deadLock->GetMutex());
		//SLog(L"! [%s]lock and [%s]lock is dead detecting", deadLock->GetName(), lock->GetName());
#endif
		return;
	}

	_lock->ProcessLock(fileName, lineNo);
	_lock->SetThreadId(GET_CURRENT_THREAD_ID);
}

LockSafeScope::~LockSafeScope()
{
	if (_lock == nullptr)
	{
		return;
	}

	/*if (_shutdown)
	{
		return;
	}*/

	_lock->Unlock();
	_lock->SetThreadId(0);
}

Lock* LockManager::SearchLockCycle(Lock* newLock)
{
	Thread* thread = ThreadManager::GetInstance().GetThread(GET_CURRENT_THREAD_ID);
	if (thread == nullptr)
	{
		return nullptr;
	}

	vector<Lock*> lockHistory;
	Lock* deadLock = nullptr;

	lockHistory.push_back(newLock);
	while (true)
	{
		Lock* threadLock = thread->GetLock();
		if (threadLock == nullptr)
		{
			break;
		}

		if (threadLock->GetLockId() == newLock->GetLockId())
		{
			deadLock = threadLock;
			break;
		}

		lockHistory.push_back(threadLock);
		thread = ThreadManager::GetInstance().GetThread(threadLock->GetThreadId());
		if (thread == nullptr)
		{
			break;
		}
	}
	
	return deadLock;
}

Lock* LockManager::CheckDeadLock(Lock* lock)
{
	Lock* deadLock = SearchLockCycle(lock);
	
	return deadLock;
}

size_t LockManager::GenerateId()
{
	size_t id = _idSeed++;

	return id;
}
