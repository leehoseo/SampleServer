#include "RecvEvent.h"
#include "BaseTime.h"
#include "TrQueueManager.h"

RecvEvent::RecvEvent(Tr* tr, const TickCount64 timer)
	: Event(EventType::Recv)
	, _tr(tr)
{
	_timer = getCurrentTimeTick64() + timer;
}

RecvEvent::~RecvEvent()
{
	delete _tr;
}


RecvEventHandle::RecvEventHandle()
{
}

RecvEventHandle::~RecvEventHandle()
{
}

void RecvEventHandle::process(Event* event)
{
	RecvEvent* trEvent = static_cast<RecvEvent*>(event);
	Tr* tr = trEvent->_tr;
	
	TrQueueManager::getInstance()->push( tr );
}
