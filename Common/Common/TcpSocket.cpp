#include "TcpSocket.h"

TcpSocket::TcpSocket(const string& address, const uint8_t& port)
	: Socket(address, port)
{
	_socket = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);	// windows
}

TcpSocket::~TcpSocket()
{

}