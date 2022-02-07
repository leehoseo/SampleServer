#include "SocketAddress.h"
#include <WS2tcpip.h>

SocketAddress::SocketAddress(const string& address, const int& port)
	: _address(address)
	, _port(port)
	, _sockAddress()
{
	memset(&_sockAddress, 0, sizeof(_sockAddress));

	_sockAddress.sin_family = AF_INET;
	_sockAddress.sin_addr.s_addr = htonl(INADDR_ANY);
	//inet_pton(AF_INET, address.c_str(), &_sockAddress.sin_addr);
	_sockAddress.sin_port = htons(port);
}

SocketAddress::~SocketAddress()
{
}

void SocketAddress::init(const string& address, const int& port)
{
	_address = address;
	_port = port;
}

const bool SocketAddress::isValied() const
{
	return (false == _address.empty()) && (0 != _port);
}

const string& SocketAddress::getIpAddress() const
{
	return _address;
}

const int& SocketAddress::getPort() const
{
	// TODO: 여기에 return 문을 삽입합니다.
	return _port;
}

const sockaddr_in& SocketAddress::getSockAddress() const
{
	return _sockAddress;
}
