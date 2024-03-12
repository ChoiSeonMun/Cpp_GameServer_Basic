#pragma once
#include "stdafx.h"

#define SAFE_LOCK(lock)		LockSafeScope __lockSafe(&lock, _W(__FILE__), __LINE__)

class Lock
{
public:
	Lock(const wchar_t* name);
	virtual ~Lock() = default;

	const wchar_t*	GetName() const;
	size_t			GetLockId() const;
	lock_t&			GetMutex();
	size_t			GetThreadId() const;

	void		SetThreadId(size_t value);

	void		ProcessLock(LPCWSTR fileName, int lineNo);
	void		Unlock();
private:
	lock_t		_mutex;
	wstr_t		_name;
	size_t		_lockId;
	size_t		_threadId;

	wstr_t		_lockingFile;
	int			_lockingLine;
};

class LockSafeScope
{
public:
	LockSafeScope(Lock* lock, LPCWSTR fileName, int lineNo);
	~LockSafeScope();
private:
	Lock* _lock;
};

class LockManager : public Singleton<LockManager>
{
public:
	Lock* SearchLockCycle(Lock* newLock);
	Lock* CheckDeadLock(Lock* lock);

	size_t	GenerateId();
private:
	size_t		_idSeed = 0;
};