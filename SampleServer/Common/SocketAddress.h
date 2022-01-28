#pragma once

#include "Base.h"
#include <WinSock2.h>

class SocketAddress
{
public:
	SocketAddress(const string& address, const uint8_t& port);
	~SocketAddress();

public:
	void init(const string& address, const uint8_t& port);
	const bool isValied() const;

	const string& getIpAddress() const;
	const uint8_t& getPort() const;

private:
	string _address;
	uint8_t _port;
	sockaddr_in _sockAddress;
};
