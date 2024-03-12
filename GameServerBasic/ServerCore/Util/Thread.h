#pragma once
#include "stdafx.h"

#define MAKE_THREAD(className, task) (new Thread(new thread_t(&className##::##task, this), _T(className))
#define GET_CURRENT_THREAD_ID hash<thread::id>{}(std::this_thread::get_id())

class Lock;
using Task = std::function<void(void*)>;

class Thread
{
public:
	Thread(thread_t* thread, wstr_t name);
	~Thread();

	size_t		GetId() const;
	wstr_t		GetName() const;
	Lock*		GetLock() const;

	void		SetLock(Lock* lock);
private:
	size_t		_id;
	wstr_t		_name;
	thread_t*	_thread;
	Lock*		_lock;
};

class ThreadManager : public Singleton<ThreadManager>
{
public:
	~ThreadManager();

	void		Put(Thread* thread);
	void		Remove(size_t id);
	Thread*		GetThread(size_t id) const;
private:
	unordered_map<size_t, Thread*> _threadPool;
};