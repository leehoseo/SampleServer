#include "PoolManager.h"

PoolManager::PoolManager()
{
    // Ŭ���̾�Ʈ�� ������ Pool ������ �޶� �� �� ���� �̰� ���� ������
 
    const int overlappedBufferPoolSize = 3;
    const int sessionPoolSize = 3;

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
