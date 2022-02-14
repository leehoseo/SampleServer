#include "PoolManager.h"

PoolManager::PoolManager()
{
    init();
}

PoolManager::~PoolManager()
{
}

void PoolManager::init()
{
    const int overlappedBufferPoolSize = 1;
    {
        _overlappedBufferPool.init(overlappedBufferPoolSize);
    }
}

Pool<OverlappedBuffer>& PoolManager::getOverlappedBufferPool()
{
    if ( false == _overlappedBufferPool.isValid())
    {
        // 에러 처리
    }

    return _overlappedBufferPool;
}
