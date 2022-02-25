#pragma once
#include "Event.h"
#include "Base.h"

class Tr;

class RecvEvent : public Event
{
public:
	RecvEvent( Tr* tr , const TickCount64 timer );
	virtual ~RecvEvent();

public:
	Tr* _tr;
};

class RecvEventHandle : public EventHandle
{
public:
	RecvEventHandle();
	~RecvEventHandle();

public:
	virtual void process( Event* event );
};
