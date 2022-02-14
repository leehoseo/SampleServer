#include "OverlappedBuffer.h"

OverlappedBuffer::OverlappedBuffer()
{
}

OverlappedBuffer::~OverlappedBuffer()
{
}

void OverlappedBuffer::init()
{
	ZeroMemory(&_overlapped, sizeof(_overlapped));
	ZeroMemory(&_wsaBuffer, sizeof(_wsaBuffer));
	ZeroMemory(&_buffer, sizeof(_buffer));
}

void OverlappedBuffer::release()
{
	__noop;
}

void OverlappedBuffer::active()
{
	__noop;
}

void OverlappedBuffer::deactive()
{
	ZeroMemory(&_overlapped, sizeof(_overlapped));
	ZeroMemory(&_wsaBuffer, sizeof(_wsaBuffer));
	ZeroMemory(&_buffer, sizeof(_buffer));
}
