#include "PoolManager.h"

PoolManager::PoolManager()
{
    // 클라이언트랑 서버랑 Pool 갯수가 달라도 될 것 같다 이건 따로 만들어보자
 
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
        // 에러 처리
    }

    return _overlappedBufferPool;
}

Pool<Session>& PoolManager::getSessionPool()
{
    if (false == _sessionPool.isValid())
    {
        // 에러 처리
    }

    return _sessionPool;
}
