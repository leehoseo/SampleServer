#include "PoolManager.h"

PoolManager::PoolManager()
{
    const int overlappedBufferPoolSize = 5;
    const int sessionPoolSize = 5;

    {
        _overlappedBufferPool.init(overlappedBufferPoolSize);
        _sessionPool.init(sessionPoolSize);
    }
}

Pool<OverlappedBuffer>& PoolManager::getOverlappedBufferPool()
{
    if ( false == _overlappedBufferPool.isValid())
    {
        // ���� ó��
    }

    return _overlappedBufferPool;
}

Pool<Session>& PoolManager::getSessionPool()
{
    if (false == _sessionPool.isValid())
    {
        // ���� ó��
    }

    return _sessionPool;
}
