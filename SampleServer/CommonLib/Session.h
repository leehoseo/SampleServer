#pragma once

#include "Socket.h"
// 플레이어에 연결되어있는 서버 통신 세션
class Session
{
public:
	Session();
	~Session();

private:
	SocketWillDelete _socket;
	SocketAddress _address;
};



