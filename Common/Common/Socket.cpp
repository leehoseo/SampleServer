#include "Socket.h"

namespace HoseoServer
{
	Socket::Socket()
		: _address("", 0)
	{
		ZeroMemory(&_receiveOverlappedBuffer, sizeof(_receiveOverlappedBuffer));
	}

	Socket::Socket(const string& address, const uint8_t& port)
		: _address(address, port)
	{
		ZeroMemory(&_receiveOverlappedBuffer, sizeof(_receiveOverlappedBuffer));
	}

	Socket::~Socket()
	{
		__noop;
	}

	void Socket::listen()
	{
		::listen(_socketHandle, 5000);
	}

	const bool Socket::bind()
	{
		if (::bind(_socketHandle, (sockaddr*)&_address, sizeof(_address)) < 0)
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

	const bool Socket::acceptOverlapped(Socket& acceptSocket)
	{
		if (_acceptExFunc == NULL)
		{
			GUID GuidAcceptEx = WSAID_ACCEPTEX;
			DWORD bytes;
			// AcceptEx�� ��Ÿ �����Լ��� �޸� ���� ȣ���ϴ� ���� �ƴϰ�,
			// �Լ� �����͸� ���� ������ ���� ȣ���� �� �ִ�. �װ��� ���⼭ �Ѵ�.
			WSAIoctl(_socketHandle,
				SIO_GET_EXTENSION_FUNCTION_POINTER,
				&GuidAcceptEx,
				sizeof(GuidAcceptEx),
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
			acceptSocket._socketHandle,
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
		WSABUF buffer;
		buffer.buf = _receiveBuffer;
		buffer.len = MAX_BUFFER_LENGTH;

		// overlapped I/O�� ����Ǵ� ���� ���� ���� ä�����ϴ�.
		_readFlags = 0;

		return WSARecv(_socketHandle, &buffer, 1, NULL, &_readFlags, &_receiveOverlappedBuffer, NULL);
	}

	const int Socket::sendOverlapped()
	{
		WSABUF buffer;
		buffer.buf = _sendBuffer;
		buffer.len = MAX_BUFFER_LENGTH;

		return WSASend(_socketHandle, &buffer, 1, NULL, 0, NULL, NULL);
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
};