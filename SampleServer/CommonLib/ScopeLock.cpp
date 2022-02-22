#include "ScopeLock.h"

ScopeLock::ScopeLock(Lock* lock)
	: _lock(lock)
{
	_lock->lock();
}

ScopeLock::~ScopeLock()
{
	_lock->unlock();
}
