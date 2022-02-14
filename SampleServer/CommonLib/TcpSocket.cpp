#include "TcpSocket.h"

TcpSocket::TcpSocket(const string& address, const int& port)
	: SocketWillDelete(address, port)
{
	_socketHandle = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);	// windows

	int zero = 0;
	setsockopt(_socketHandle, SOL_SOCKET, SO_SNDBUF, (char*)&zero, sizeof(zero));
	setsockopt(_socketHandle, SOL_SOCKET, SO_RCVBUF, (char*)&zero, sizeof(zero));
}

TcpSocket::TcpSocket()
	: SocketWillDelete()
{
	_socketHandle = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);	// windows

	// https://snowfleur.tistory.com/193?category=756631
	// Page Locking �ּ�ȭ�� ���� �� ���� ���۸� 0���� ������
	// Ŀ�� ���������� �ۼ��Ź��۸� �̿����� �ʰ� ���ø����̼ǿ��� �����ϴ� ���۷� �ٷ� ���縦 �ع����� ������ 
	// ���� Ƚ���� �� �� �پ� �ӵ��� ������ ��������.

	int zero = 0;
	setsockopt(_socketHandle, SOL_SOCKET, SO_SNDBUF, (char*)&zero, sizeof(zero));
	setsockopt(_socketHandle, SOL_SOCKET, SO_RCVBUF, (char*)&zero, sizeof(zero));
}


TcpSocket::~TcpSocket()
{
	closesocket(_socketHandle);
}
