#include "OverlappedBuffer.h"

OverlappedBuffer::OverlappedBuffer()
{
	init();
}

OverlappedBuffer::~OverlappedBuffer()
{
}

void OverlappedBuffer::init()
{
	ZeroMemory(&_overlapped, sizeof(_overlapped));
	ZeroMemory(&_wsaBuffer, sizeof(_wsaBuffer));
	ZeroMemory(&_buffer, sizeof(_buffer));

	_sessionKey.clear();
	_type = BufferType::COUNT;
}

void OverlappedBuffer::release()
{
	__noop;
}

void OverlappedBuffer::active()
{
	_wsaBuffer.len = MAX_BUFFER;
	_wsaBuffer.buf = _buffer;
}

void OverlappedBuffer::deactive()
{
	init();
}
