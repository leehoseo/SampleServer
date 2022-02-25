#include "Lock.h"

Lock::Lock()
{
}

Lock::~Lock()
{
}

void Lock::lock()
{
	_lock.lock();
}

void Lock::unlock()
{
	_lock.unlock();
}

std::mutex& Lock::get()
{
	return _lock;
}
