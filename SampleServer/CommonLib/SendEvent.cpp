#include "SendEvent.h"
#include "BaseTime.h"
#include "TrQueueManager.h"
#include "SystemManager.h"
#include "Iocp.h"
#include "Dispatcher.h"

SendEvent::SendEvent(Tr* tr, const TickCount64 timer, const std::vector<Session_ID>& sessionIdList)
	: Event(EventType::Send)
	, _tr(tr)
{
	_timer = getCurrentTimeTick64() + timer;
	_sessionIdList = sessionIdList;
}

SendEvent::SendEvent(Tr* tr, const TickCount64 timer, const Session_ID& sessionId)
	: Event(EventType::Send)
	, _tr(tr)
{
	_timer = getCurrentTimeTick64() + timer;
	_sessionIdList.push_back(sessionId);
}

SendEvent::~SendEvent()
{
}

SendEventHandle::SendEventHandle()
{
}

SendEventHandle::~SendEventHandle()
{
}

void SendEventHandle::process(Event* event)
{
	SendEvent* sendEvent = static_cast<SendEvent*>(event);
	Tr* tr = sendEvent->_tr;

 	Iocp* iocp = SystemManager::getInstance()->getIcop();

	iocp->send(sendEvent->_sessionIdList, sendEvent->_tr);
}

void makeSendEventToServer(Tr* tr, const TickCount64 timer)
{
	SendEvent* sendEvent = new SendEvent(tr, timer, SystemManager::getInstance()->getIcop()->getMainSessionId());
	Dispatcher::getInstance()->push(sendEvent);
}

void makeSendEventToClient(Tr* tr, const TickCount64 timer, const std::vector<Session_ID>& sessionIdList)
{
	SendEvent* sendEvent = new SendEvent(tr, timer, sessionIdList);
	Dispatcher::getInstance()->push(sendEvent);
}

void makeSendEventToClient(Tr* tr, const TickCount64 timer, const Session_ID& sessionId)
{
	SendEvent* sendEvent = new SendEvent(tr, timer, sessionId);
	Dispatcher::getInstance()->push(sendEvent);
}
