#include "Tr.h"
#include "SendEvent.h"
#include "Dispatcher.h"

Tr::Tr()
{
}


Tr::Tr(const TrId trId, const ThreadType type, const int maxSize)
	: _type(type)
	, _maxSize(maxSize)
	, _trId(trId)
{
}

Tr::~Tr()
{
}

void Tr::send(Tr* tr, const TickCount64 timer, const SessionKey& sessionKey)
{
	Tr* newTr = new Tr(*this);

	SendEvent* sendEvent = new SendEvent(tr, timer, sessionKey);
	Dispatcher::getInstance()->push(sendEvent);
}