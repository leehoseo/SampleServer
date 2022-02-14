#pragma once

#include "Pool.h"
#include "PoolItem.h"
#include <winsock2.h>

#define MAX_BUFFER      1024
class OverlappedBuffer : public PoolItem
{
public:
    OverlappedBuffer();
    ~OverlappedBuffer();

public:
	// ������ �ʱ�ȭ �Ǵ� �����ö�
	virtual void init() override final;

	// �ı��ɶ�
	virtual void release() override final;


	// pop
	virtual void active() override final;

	// push
	virtual void deactive() override final;

public:
    WSAOVERLAPPED   _overlapped;
    WSABUF          _wsaBuffer;
    char            _buffer[MAX_BUFFER];
};


