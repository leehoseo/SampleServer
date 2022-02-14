#pragma once

#include "Singleton.h"
#include "Pool.h"
#include "OverlappedBuffer.h"

class PoolManager : public Singleton<PoolManager>
{
private:
	PoolManager();

private:
	virtual ~PoolManager();

public:
	void init();

	Pool<OverlappedBuffer>& getOverlappedBufferPool();

private:
	Pool<OverlappedBuffer> _overlappedBufferPool;
};

