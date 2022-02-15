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
    static SESSION_ID sessionCount = 0;
    _id = ++sessionCount;

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

void Session::setSocketAddr(const std::string& address, const int& port, const bool isServer)
{
    _address.init(address, port, isServer);
}

SocketAddress& Session::getSocketAddr()
{
    return _address;
}

SOCKET& Session::getSocketHandle()
{
    return _socket.getHandle();
}

const SESSION_ID& Session::getSessionId()
{
    return _id;
}
