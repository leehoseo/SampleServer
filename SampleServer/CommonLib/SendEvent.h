#pragma once
#include "Event.h"
#include "Base.h"
#include <vector>

class Tr;

class SendEvent : public Event
{
public:
	SendEvent(Tr* tr, const TickCount64 timer, const std::vector<Session_ID>& sessionIdList);
	virtual ~SendEvent();

public:
	Tr* _tr;
	TickCount64 _timer;
	std::vector<Session_ID> _sessionIdList;
};

class SendEventHandle : public EventHandle
{
public:
	SendEventHandle();
	~SendEventHandle();

public:
	virtual void process(Event* event);
};
