#pragma once
#include "Event.h"
#include "Base.h"

class Tr;

class TrEvent : public Event
{
public:
	TrEvent( Tr* tr , const TickCount64 timer );
	virtual ~TrEvent();

public:
	Tr* _tr;
	TickCount64 _timer;
};

class TrEventHandle : public EventHandle
{
public:
	TrEventHandle();
	~TrEventHandle();

public:
	virtual void process( Event* event );
};
