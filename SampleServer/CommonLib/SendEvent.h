#pragma once
#include "Event.h"
#include "Base.h"
#include <vector>

class Tr;

class SendEvent : public Event
{
public:
	SendEvent(Tr* tr, const TickCount64 timer, const std::vector<Session_ID>& sessionIdList);
	SendEvent(Tr* tr, const TickCount64 timer, const Session_ID& sessionId);
	virtual ~SendEvent();

public:
	Tr* _tr;
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

void makeSendEventToServer(Tr* tr, const TickCount64 timer);
void makeSendEventToClient(Tr* tr, const TickCount64 timer, const std::vector<Session_ID>& sessionIdList);
void makeSendEventToClient(Tr* tr, const TickCount64 timer, const Session_ID& sessionId);