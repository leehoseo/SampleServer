#pragma once

#include "Base.h"
#include <WinSock2.h>

class SocketAddress
{
public:
	SocketAddress(const string& address, const int& port);
	~SocketAddress();

public:
	void init(const string& address, const int& port);
	const bool isValied() const;

	const string& getIpAddress() const;
	const int& getPort() const;
	const sockaddr_in& getSockAddress() const;

	sockaddr_in _sockAddress;
private:
	string _address;
	int _port;
};
