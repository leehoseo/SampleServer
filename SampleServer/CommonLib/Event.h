#pragma once
#include "Time.h"

enum class EventType
{
	Tr = 0,
	Action,
	Logger,
	Count,
};

class Event
{
public:
	Event(const EventType& type);
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
	~EventHandle();

public:
	virtual void process(Event* event) = 0;
};
