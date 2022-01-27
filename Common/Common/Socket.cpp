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
			// AcceptEx는 여타 소켓함수와 달리 직접 호출하는 것이 아니고,
			// 함수 포인터를 먼저 가져온 다음 호출할 수 있다. 그것을 여기서 한다.
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


		// 여기에는 accept된 소켓의 로컬주소와 리모트주소가 채워집니다
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

		// overlapped I/O가 진행되는 동안 여기 값이 채워집니다.
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