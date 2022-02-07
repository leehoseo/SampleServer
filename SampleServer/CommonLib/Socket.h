#pragma once

#include "Base.h"
#include "SocketAddress.h"

#define _WINSOCKAPI_
#include <windows.h>
#include <MSWSock.h>

class Socket
{
public:
	Socket();
	Socket(const string& address, const int& port);
	~Socket();

public:
	// ��ſ�
	void		init(const string& address, const int& port);
	void		listen();
	const bool	bind();
	const bool	connect();
	const bool	acceptOverlapped(Socket* acceptSocket); // accept �غ�
	const int	receiveOverlapped(); // overlapeed ���� �غ� ( ��׶��忡�� ���� ó���� ��)
	const int	sendOverlapped(); // overlapeed ���� �غ� ( ��׶��忡�� ���� ó���� ��)
	const int	updateAcceptContext(Socket* listenSocket);
	// ���� Ȯ�ο� 
	const bool	isOverlapping() const;
	void		setIsOverlapping(const bool isOverlapping);

	const SOCKET& getHandle() const;

	void		getReceiveBuffer(char* outBuffer);
	void		setSendBuffer(const char* sendBuffer);
	SOCKET _socketHandle; // ���� �ڵ�
	SocketAddress _address;
	WSABUF _buffer;
	WSABUF _buffer2;
protected:

private:
	static const int MAX_BUFFER_LENGTH = 1024;


	// AcceptEx �Լ� ������
	LPFN_ACCEPTEX _acceptExFunc = nullptr;

	// I/O������
	bool _isOverlapping = false;

	// Overlapped receive or accept�� �� �� ���Ǵ� overlapped ��ü�Դϴ�. 
	// I/O �Ϸ� �������� �����Ǿ�� �մϴ�.
	WSAOVERLAPPED _receiveOverlappedBuffer;
	// overlapped ������ �ϴ� ���� ���⿡ recv�� flags�� ���ϴ� ���� ä�����ϴ�.
	// overlapped I/O�� ����Ǵ� ���� �� ���� �ǵ帮�� ������.
	DWORD _readFlags = 0;

	char _receiveBuffer[MAX_BUFFER_LENGTH];
	char _sendBuffer[MAX_BUFFER_LENGTH];
};
