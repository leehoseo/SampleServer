#pragma once

#define _WINSOCKAPI_
#include <windows.h>
#include <WinSock2.h>
//#include <MSWSock.h>


class Socket
{
public:
	Socket();
	virtual ~Socket();

public:
	SOCKET& getHandle();

private:
	SOCKET _handle; // 소켓 핸들
};