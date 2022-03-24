#include "Event.h"

Event::Event(const EventType& type, const TickCount64 timer)
	: _type(type)
{
	if (0 != timer)
	{
		_timer = getCurrentTimeTick64() + timer;
	}
}

Event::~Event()
{
}

EventHandle::EventHandle()
{
}

EventHandle::~EventHandle()
{
}
