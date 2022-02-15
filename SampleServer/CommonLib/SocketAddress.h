#pragma once

#include "Base.h"
#include <string>
#include <WinSock2.h>

class SocketAddress
{
public:
	SocketAddress();
	~SocketAddress();

public:
	void init(const std::string& address, const int& port, const bool isServer);
	const bool isValied() const;

	const std::string& getIp() const;
	const int& getPort() const;
	sockaddr_in& getSockAddress();

	sockaddr_in _sockAddress;
private:
	std::string _address;
	int _port;
};
