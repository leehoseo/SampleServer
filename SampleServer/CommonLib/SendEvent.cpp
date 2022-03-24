#include "SendEvent.h"
#include "BaseTime.h"
#include "SystemManager.h"
#include "Iocp.h"

SendEvent::SendEvent(Tr* tr, const TickCount64 timer, const std::vector<SessionKey>& sessionKeyList)
	: Event(EventType::Send, timer)
	, _tr(tr)
{
	_sessionKeyList = sessionKeyList;
}

SendEvent::SendEvent(Tr* tr, const TickCount64 timer, const SessionKey& sessionKey)
	: Event(EventType::Send, timer)
	, _tr(tr)
{
	_sessionKeyList.push_back(sessionKey);
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

	iocp->send(sendEvent->_sessionKeyList, sendEvent->_tr);

	delete tr;
}