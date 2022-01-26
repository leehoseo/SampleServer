#include "Socket.h"

Socket::Socket(const string& address, const uint8_t& port)
	:_address(address, port)
{
	__noop;
}

Socket::~Socket()
{
	__noop;
}

const bool Socket::socketBind()
{
	if (bind(_socket, (sockaddr*)&_address, sizeof(_address)) < 0)
	{
		cout << "bind failed:" << endl;
		return false;
	}

	return true;
}

const bool Socket::socketConnect()
{
	if (connect(_socket, (sockaddr*)&_address, sizeof(_address)) < 0)
	{
		cout << "connect failed:" << endl;
		return false;
	}

	return true;
}

const bool Socket::socketAccept()
{
	return false;
}