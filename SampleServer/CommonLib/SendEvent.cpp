#include "SendEvent.h"
#include "BaseTime.h"
#include "TrQueueManager.h"
#include "SystemManager.h"
#include "Iocp.h"

SendEvent::SendEvent(Tr* tr, const TickCount64 timer, const std::vector<Session_ID>& sessionIdList)
	: Event(EventType::Send)
	, _tr(tr)
{
	_timer = getCurrentTimeTick64() + timer;
	_sessionIdList = sessionIdList;
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
