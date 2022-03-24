#include "RecvEvent.h"
#include "BaseTime.h"
#include "TrQueueManager.h"
#include "Dispatcher.h"

#pragma optimize ("", off)

RecvEvent::RecvEvent(Tr* tr, const TickCount64 timer)
	: Event(EventType::Recv, timer)
	, _tr(tr)
{

}

RecvEvent::~RecvEvent()
{
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