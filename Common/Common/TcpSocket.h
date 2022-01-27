#pragma once
#include "Socket.h"

namespace HoseoServer
{
	class TcpSocket : public Socket
	{
	public:
		TcpSocket(const string& address, const uint8_t& port);
		TcpSocket();
		virtual ~TcpSocket();
	};

};