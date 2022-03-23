#pragma once
#include "Event.h"
#include "Base.h"
#include <vector>

class Tr;
class SendEvent : public Event
{
public:
	SendEvent(Tr* tr, const TickCount64 timer, const std::vector<SessionKey>& sessionKeyList);
	SendEvent(Tr* tr, const TickCount64 timer, const SessionKey& sessionKey);
	virtual ~SendEvent();

public:
	Tr* _tr;
	std::vector<SessionKey> _sessionKeyList;
};

class SendEventHandle : public EventHandle
{
public:
	SendEventHandle();
	~SendEventHandle();

public:
	virtual void process(Event* event);
};