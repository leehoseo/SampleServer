#include "Socket.h"

Socket::Socket()
	: _address("", 0)
{
	ZeroMemory(&_receiveOverlappedBuffer, sizeof(_receiveOverlappedBuffer));
}

Socket::Socket(const string& address, const int& port)
	: _address(address, port)
{
	ZeroMemory(&_receiveOverlappedBuffer, sizeof(_receiveOverlappedBuffer));
}

Socket::~Socket()
{
	__noop;
}

void Socket::init(const string& address, const int& port)
{
	_address.init(address, port);
}

void Socket::listen()
{
	::listen(_socketHandle, 5000);
}

const bool Socket::bind()
{
	if (::bind(_socketHandle, (sockaddr*)&_address._sockAddress, sizeof(_address._sockAddress)) < 0)
	{
		cout << "bind failed:" << endl;
		return false;
	}

	return true;
}

const bool Socket::connect()
{
	if (::connect(_socketHandle, (sockaddr*)&_address, sizeof(_address)) < 0)
	{
		cout << "connect failed:" << endl;
		return false;
	}

	return true;
}

const bool Socket::acceptOverlapped(Socket* acceptSocket)
{
	if (_acceptExFunc == NULL)
	{
		UUID GuidAcceptEx = WSAID_ACCEPTEX;
		DWORD bytes;
		// AcceptEx�� ��Ÿ �����Լ��� �޸� ���� ȣ���ϴ� ���� �ƴϰ�,
		// �Լ� �����͸� ���� ������ ���� ȣ���� �� �ִ�. �װ��� ���⼭ �Ѵ�.
		WSAIoctl(_socketHandle,
			SIO_GET_EXTENSION_FUNCTION_POINTER,
			&GuidAcceptEx,
			sizeof(UUID),
			&_acceptExFunc,
			sizeof(_acceptExFunc),
			&bytes,
			NULL,
			NULL);

		if (_acceptExFunc == NULL)
		{
			cout << "Getting AcceptEx ptr failed." << endl;
			return false;
		}
	}


	// ���⿡�� accept�� ������ �����ּҿ� ����Ʈ�ּҰ� ä�����ϴ�
	char ignored[200];
	DWORD ignored2 = 0;

	bool result = AcceptEx(_socketHandle,
		acceptSocket->_socketHandle,
		&ignored,
		0,
		50,
		50,
		&ignored2,
		&_receiveOverlappedBuffer
	);

	return result;
}

const int Socket::receiveOverlapped()
{
	_buffer.buf = _receiveBuffer;
	_buffer.len = MAX_BUFFER_LENGTH;
	int RecvBytes = 0;
	// overlapped I/O�� ����Ǵ� ���� ���� ���� ä�����ϴ�.
	_readFlags = 0;

	return WSARecv(_socketHandle, &_buffer, 1, (LPDWORD)&RecvBytes, &_readFlags, &_receiveOverlappedBuffer, NULL);
}

const int Socket::sendOverlapped()
{
	_buffer2.buf = _sendBuffer;
	_buffer2.len = MAX_BUFFER_LENGTH;
	int sendBytes = 0;
	return WSASend(_socketHandle, &_buffer2, 1, (LPDWORD)&sendBytes, 0, &_receiveOverlappedBuffer, NULL);
}

const int Socket::updateAcceptContext(Socket* listenSocket)
{
	sockaddr_in localAddr;
	sockaddr_in remoteAddr;
	int localLen = 0;
	int remoteLen = 0;

	char ignore[1000];
	GetAcceptExSockaddrs(ignore,
		0,
		sizeof(SOCKADDR_STORAGE) + 16,
		sizeof(SOCKADDR_STORAGE) + 16,
		(sockaddr**)&localAddr,
		&localLen,
		(sockaddr**)&remoteAddr,
		&remoteLen);

	memcpy(&_address._sockAddress, &localAddr, localLen);

	return setsockopt(_socketHandle, SOL_SOCKET, SO_UPDATE_ACCEPT_CONTEXT,
		(char*)&listenSocket->getHandle(), sizeof(listenSocket->getHandle()));
}

void Socket::getReceiveBuffer(char* outBuffer)
{
	outBuffer = _receiveBuffer;
}

void Socket::setSendBuffer(const char* sendBuffer)
{
	memset(_sendBuffer, 0, MAX_BUFFER_LENGTH);
	strcat_s(_sendBuffer, MAX_BUFFER_LENGTH, sendBuffer);
}

const SOCKET& Socket::getHandle() const
{
	return _socketHandle;
}

const bool Socket::isOverlapping() const
{
	return _isOverlapping;
}

void Socket::setIsOverlapping(const bool isOverlapping)
{
	_isOverlapping = isOverlapping;
}
