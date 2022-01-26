#pragma once

#include "Base.h"
#include "SocketAddress.h"

#include <WinSock2.h>
#include <windows.h>
#include <mswsock.h>

class Socket
{
public:
	Socket(const string& address, const uint8_t& port);
	~Socket();

public:
	const bool socketBind();
	const bool socketConnect();
	const bool socketAccept();

protected:
	SOCKET _socket; // ���� �ڵ�

private:
	SocketAddress _address;
};

