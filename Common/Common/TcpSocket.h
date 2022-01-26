#pragma once
#include "Socket.h"

class TcpSocket : public Socket
{
public: 
	TcpSocket(const string& address, const uint8_t& port);
	virtual ~TcpSocket();
};

