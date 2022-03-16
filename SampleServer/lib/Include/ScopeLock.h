#pragma once
#include "Lock.h"

class ScopeLock
{
public:
	ScopeLock(Lock* lock);
	~ScopeLock();

private:
	Lock* _lock;
};

