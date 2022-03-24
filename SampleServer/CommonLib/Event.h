#pragma once
#include "BaseTime.h"

enum class EventType
{
	Recv = 0,
	Send,
	Action,
	Logger,
	Count,
};

class Event
{
public:
	Event(const EventType& type, const TickCount64 timer);
	virtual ~Event();


public:
	bool operator<(const Event s) const
	{
		return this->_timer > s._timer;
	}
public:
	TickCount64 _timer = 0;
	EventType _type = EventType::Count;
};

class EventHandle
{
public:
	EventHandle();
	virtual ~EventHandle();

public:
	virtual void process(Event* event) = 0;
};
