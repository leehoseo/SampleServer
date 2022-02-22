#include "Event.h"

Event::Event(const EventType& type)
	: _type(type)
{}

Event::~Event()
{
}

EventHandle::EventHandle()
{
}

EventHandle::~EventHandle()
{
}
