#pragma once

#include "Base.h"
#include "Pool.hpp"
#include <winsock2.h>

enum class BufferType
{
	UNDEFINED = 0,
	ACCEPT,
	SEND,
	RECV,
	DISCONNECT,
	CONNECT,
	COUNT,
};

class OverlappedBuffer// : public IPoolItem
{
public:
    OverlappedBuffer();
    ~OverlappedBuffer();

public:
	// ������ �ʱ�ȭ �Ǵ� �����ö�
	void init();

	// �ı��ɶ�
	void release();

	// pop
	void active();

	// push
	void deactive();

public:
	WSAOVERLAPPED   _overlapped;
	WSABUF          _wsaBuffer;
	char            _buffer[MAX_BUFFER];
	SessionKey		_sessionKey;
	BufferType		_type;
};