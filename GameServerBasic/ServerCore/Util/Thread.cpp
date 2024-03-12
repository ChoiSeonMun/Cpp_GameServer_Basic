#include "stdafx.h"
#include "Thread.h"


Thread::Thread(thread_t* thread, wstr_t name)
	: _name{ name }, _thread{ thread }
{
	_id = hash<thread::id>{}(_thread->get_id());

	ThreadManager::GetInstance().Put(this);
}

Thread::~Thread()
{
	_thread->join();

	SAFE_DELETE(_thread);
	SAFE_DELETE(_lock);
}

size_t Thread::GetId() const
{
	return _id;
}

wstr_t Thread::GetName() const
{
	return _name;
}

Lock* Thread::GetLock() const
{
	return _lock;
}

void Thread::SetLock(Lock* lock)
{
	_lock = lock;
}

ThreadManager::~ThreadManager()
{
	for (auto thread : _threadPool)
	{
		SAFE_DELETE(thread.second);
	}
}

void ThreadManager::Put(Thread* thread)
{
	_threadPool.emplace(thread->GetId(), thread);
	// SLog(L"* create thread : id[0x%X] name[%s], pool size[%d]", thread->id(), thread->name().c_str(), _threadPool.size());
}

void ThreadManager::Remove(size_t id)
{
	auto iter = _threadPool.find(id);
	if (iter == _threadPool.end())
	{
		return;
	}
	_threadPool.erase(iter);
}

Thread* ThreadManager::GetThread(size_t id) const
{
	if (auto iter = _threadPool.find(id); iter == _threadPool.end())
	{
		return nullptr;
	}
	else
	{
		auto thread = iter->second;
		return thread;
	}
}

