#include "ServerNetworkContents.h"
#include "Tr.h"
#include "TrChatProc.h"

#pragma optimize("", off)

ServerNetworkContents::ServerNetworkContents()
{
}

ServerNetworkContents::~ServerNetworkContents()
{
}

void ServerNetworkContents::recvTr(Tr* tr)
{
#define CaseHandle(trId) case TrId::##trId: { trId##Proc proc; proc.process(tr); } break;

	switch (tr->_trId)
	{
		CaseHandle(TrChatReq);
	}
}
