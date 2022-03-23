#include "NetworkContents.h"
#include "Proc.h"
#include "Tr.h"
#include "SystemManager.h"
#include "SendEvent.h"
#include "RecvEvent.h"
#include "Dispatcher.h"

#pragma optimize("", off)

NetworkContents::NetworkContents()
{
}

NetworkContents::~NetworkContents()
{
}

void NetworkContents::sendToServer(Tr* tr, const TickCount64 timer)
{
	SendEvent* sendEvent = new SendEvent(tr, timer, SystemManager::getInstance()->getIcop()->getMainSessionKey());
	Dispatcher::getInstance()->push(sendEvent);
}

void NetworkContents::recvTrEvent(Tr* tr, const TickCount64 timer)
{
	RecvEvent* recvEvent = new RecvEvent(tr, timer);
	Dispatcher::getInstance()->push(recvEvent);
}

void NetworkContents::recvTr(Tr* tr)
{
	Proc* proc =  ProcManager::getInstance()->getProc(tr->_trId);
	if (nullptr == proc)
	{
		// ¿¡·¯
		return;
	}

	proc->process(tr);
}