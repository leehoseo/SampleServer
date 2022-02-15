#include "SocketAddress.h"
#include <WS2tcpip.h>

SocketAddress::SocketAddress()
{
}

SocketAddress::~SocketAddress()
{
}

void SocketAddress::init(const std::string& address, const int& port, const bool isServer)
{
	_address = address;
	_port = port;

	memset(&_sockAddress, 0, sizeof(_sockAddress));

	_sockAddress.sin_family = AF_INET;

	//inet_pton(AF_INET, address.c_str(), &_sockAddress.sin_addr);
	_sockAddress.sin_port = htons(port);

	if (true == isServer)
	{
		_sockAddress.sin_addr.s_addr = htonl(INADDR_ANY);
	}
	else
	{
		inet_pton(AF_INET, address.c_str(), &_sockAddress.sin_addr.s_addr);
	}
}

const bool SocketAddress::isValied() const
{
	return (false == _address.empty()) && (0 != _port);
}

const std::string& SocketAddress::getIp() const
{
	return _address;
}

const int& SocketAddress::getPort() const
{
	// TODO: 여기에 return 문을 삽입합니다.
	return _port;
}

sockaddr_in& SocketAddress::getSockAddress()
{
	return _sockAddress;
}
