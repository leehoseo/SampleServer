#include "TrEvent.h"
#include "Time.h"
#include "Thread.h"
#include "TrQueueManager.h"

TrEvent::TrEvent(Tr* tr, const TickCount64 timer)
	: Event(EventType::Tr)
	, _tr(tr)
{
	_timer = getCurrentTimeTick64() + timer;
}

TrEvent::~TrEvent()
{
	delete _tr;
}


TrEventHandle::TrEventHandle()
{
}

TrEventHandle::~TrEventHandle()
{
}

void TrEventHandle::process(Event* event)
{
	TrEvent* trEvent = static_cast<TrEvent*>(event);
	Tr* tr = trEvent->_tr;
	
	TrQueueManager::getInstance()->push( tr );
}
