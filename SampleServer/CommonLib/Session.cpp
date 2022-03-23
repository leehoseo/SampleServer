#include "Session.h"
#include "OverlappedBuffer.h"
#include "PoolManager.h"
#include "Logger.h"

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib,"mswsock.lib")

Session::Session()
{
}

Session::~Session()
{
}


void Session::init()
{
    static SessionKey::Type sessionCount = SessionKey::undefined;
    _key = ++sessionCount;

    if (INT_MAX <= sessionCount)
    {
        Logger::getInstance()->log(Logger::Level::WARNING, "sessionSize Overflow");
    }
}

void Session::release()
{

}

void Session::active()
{
    __noop;
}

void Session::deactive()
{
    __noop;
}

SOCKET& Session::getSocketHandle()
{
    return _socket.getHandle();
}

const SessionKey& Session::getSessionKey()
{
    return _key;
}
