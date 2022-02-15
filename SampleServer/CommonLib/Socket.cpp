#include "Socket.h"

#pragma optimize ("" , off )
Socket::Socket()
{
	_handle = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);	// windows

	{
		// https://snowfleur.tistory.com/193?category=756631
		// Page Locking �ּ�ȭ�� ���� �� ���� ���۸� 0���� ������
		// Ŀ�� ���������� �ۼ��Ź��۸� �̿����� �ʰ� ���ø����̼ǿ��� �����ϴ� ���۷� �ٷ� ���縦 �ع����� ������ 
		// ���� Ƚ���� �� �� �پ� �ӵ��� ������ ��������.
		int zero = 0;
		setsockopt(_handle, SOL_SOCKET, SO_SNDBUF, (char*)&zero, sizeof(zero));
		setsockopt(_handle, SOL_SOCKET, SO_RCVBUF, (char*)&zero, sizeof(zero));
	}
}

Socket::~Socket()
{
	closesocket(_handle);
}

SOCKET& Socket::getHandle()
{
	return _handle;
}
