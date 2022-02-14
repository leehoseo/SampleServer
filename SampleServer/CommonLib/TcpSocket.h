#pragma once
#include "Socket.h"

class TcpSocket : public SocketWillDelete
{
public:
	TcpSocket(const string& address, const int& port);
	TcpSocket();
	virtual ~TcpSocket();
};
