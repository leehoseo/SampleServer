#include "Socket.h"

SocketWillDelete::SocketWillDelete()
	: _address("", 0)
{
	ZeroMemory(&_receiveOverlappedBuffer, sizeof(_receiveOverlappedBuffer));
}

SocketWillDelete::SocketWillDelete(const string& address, const int& port)
	: _address(address, port)
{
	ZeroMemory(&_receiveOverlappedBuffer, sizeof(_receiveOverlappedBuffer));
}

SocketWillDelete::~SocketWillDelete()
{
	__noop;
}

void SocketWillDelete::init(const string& address, const int& port)
{
	_address.init(address, port);
}

void SocketWillDelete::listen()
{
	::listen(_socketHandle, 5000);
}

const bool SocketWillDelete::bind()
{
	if (::bind(_socketHandle, (sockaddr*)&_address._sockAddress, sizeof(_address._sockAddress)) < 0)
	{
		cout << "bind failed:" << endl;
		return false;
	}

	return true;
}

const bool SocketWillDelete::connect()
{
	if (::connect(_socketHandle, (sockaddr*)&_address, sizeof(_address)) < 0)
	{
		cout << "connect failed:" << endl;
		return false;
	}

	return true;
}

const bool SocketWillDelete::acceptOverlapped(SocketWillDelete* acceptSocket)
{
	//if (_acceptExFunc == NULL)
	//{
	//	UUID GuidAcceptEx = WSAID_ACCEPTEX;
	//	DWORD bytes;
	//	// AcceptEx�� ��Ÿ �����Լ��� �޸� ���� ȣ���ϴ� ���� �ƴϰ�,
	//	// �Լ� �����͸� ���� ������ ���� ȣ���� �� �ִ�. �װ��� ���⼭ �Ѵ�.
	//	WSAIoctl(_socketHandle,
	//		SIO_GET_EXTENSION_FUNCTION_POINTER,
	//		&GuidAcceptEx,
	//		sizeof(UUID),
	//		&_acceptExFunc,
	//		sizeof(_acceptExFunc),
	//		&bytes,
	//		NULL,
	//		NULL);

	//	if (_acceptExFunc == NULL)
	//	{
	//		cout << "Getting AcceptEx ptr failed." << endl;
	//		return false;
	//	}
	//}


	// ���⿡�� accept�� ������ �����ּҿ� ����Ʈ�ּҰ� ä�����ϴ�
	char ignored[200];
	DWORD ignored2 = 0;

	bool result = AcceptEx(_socketHandle,
		acceptSocket->_socketHandle,
		&ignored,
		0,
		sizeof(SOCKADDR_IN) + 16,
		sizeof(SOCKADDR_IN) + 16,
		&ignored2,
		&_receiveOverlappedBuffer
	);

	return result;
}

const int SocketWillDelete::receiveOverlapped()
{
	_buffer.buf = _receiveBuffer;
	_buffer.len = MAX_BUFFER_LENGTH;
	int RecvBytes = 0;
	// overlapped I/O�� ����Ǵ� ���� ���� ���� ä�����ϴ�.
	_readFlags = 0;

	return WSARecv(_socketHandle, &_buffer, 1, (LPDWORD)&RecvBytes, &_readFlags, &_receiveOverlappedBuffer, NULL);
}

const int SocketWillDelete::sendOverlapped()
{
	OVER_EX* over_ex = new OVER_EX;
	ZeroMemory(&over_ex->over_, sizeof(over_ex->over_));

	over_ex->wsabuf_.len = 1024;
	over_ex->wsabuf_.buf = over_ex->buffer_;

	memcpy(over_ex->buffer_, &_sendBuffer, 1024);

	int sendBytes = 0;
	return WSASend(_socketHandle, &over_ex->wsabuf_, 1, 0, 0, &over_ex->over_, NULL);
}

void SocketWillDelete::getReceiveBuffer(char* outBuffer)
{
	outBuffer = _receiveBuffer;
}

void SocketWillDelete::setSendBuffer(const char* sendBuffer)
{
	memset(_sendBuffer, 0, MAX_BUFFER_LENGTH);
	strcat_s(_sendBuffer, MAX_BUFFER_LENGTH, sendBuffer);
}

const SOCKET& SocketWillDelete::getHandle() const
{
	return _socketHandle;
}

const bool SocketWillDelete::isOverlapping() const
{
	return _isOverlapping;
}

void SocketWillDelete::setIsOverlapping(const bool isOverlapping)
{
	_isOverlapping = isOverlapping;
}

Socket::Socket()
{
}

Socket::~Socket()
{
}

void Socket::init()
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

void Socket::release()
{
}

void Socket::active()
{
}

void Socket::deactive()
{
}
