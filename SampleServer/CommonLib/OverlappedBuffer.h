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
	// 생성시 초기화 또는 가져올때
	virtual void init() override final;

	// 파괴될때
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


