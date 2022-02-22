#pragma once

#include "Singleton.h"
#include "Pool.hpp"
#include "OverlappedBuffer.h"
#include "Session.h"

class PoolManager : public Singleton<PoolManager>
{
public:
	PoolManager();
	virtual ~PoolManager() {};

public:
	Pool<OverlappedBuffer>& getOverlappedBufferPool();
	Pool<Session>&			getSessionPool();


private:
	Pool<OverlappedBuffer> _overlappedBufferPool;
	Pool<Session> _sessionPool;
};

