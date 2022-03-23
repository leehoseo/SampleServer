#include "NetworkContents.h"
#include "Proc.h"
#include "Tr.h"

#pragma optimize("", off)

NetworkContents::NetworkContents()
{
}

NetworkContents::~NetworkContents()
{
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