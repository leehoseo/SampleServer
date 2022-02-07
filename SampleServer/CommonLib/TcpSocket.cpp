#include "TcpSocket.h"

TcpSocket::TcpSocket(const string& address, const int& port)
	: Socket(address, port)
{
	_socketHandle = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);	// windows
}

TcpSocket::TcpSocket()
	: Socket()
{
	_socketHandle = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);	// windows
}


TcpSocket::~TcpSocket()
{
	closesocket(_socketHandle);
}
