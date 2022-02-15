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

	_session_id = undefinedSessionId;
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
	ZeroMemory(&_overlapped, sizeof(_overlapped));
	ZeroMemory(&_wsaBuffer, sizeof(_wsaBuffer));
	ZeroMemory(&_buffer, sizeof(_buffer));

	_session_id = undefinedSessionId;
	_type = BufferType::COUNT;
}
