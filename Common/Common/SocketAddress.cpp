#include "SocketAddress.h"
#include <WS2tcpip.h>

SocketAddress::SocketAddress(const string& address, const uint8_t& port)
	: _address(address)
	, _port(port)
	, _sockAddress()
{
	_sockAddress.sin_family = AF_INET;
	inet_pton(AF_INET, address.c_str(), &_sockAddress.sin_addr);
	_sockAddress.sin_port = htons(port);
}

SocketAddress::~SocketAddress()
{
}

const bool SocketAddress::isValied() const
{
	return (false == _address.empty()) && ( 0 != _port );
}

const string& SocketAddress::getIpAddress() const
{
	return _address;
}

const uint8_t& SocketAddress::getPort() const
{
	// TODO: 여기에 return 문을 삽입합니다.
	return _port;
}
