#include "TrChatProc.h"
#include "TrChat.h"
#include "Logger.h"

void TrChatReqProc::process(Tr* tr)
{
	TrChatReqPacket* chatReq = static_cast<TrChatReqPacket*>(tr);

	// ����
	{
		// �� ��Ʈ�� �׷��� �ϸ� �ɵ�
	}
	
	std::string chatStr = "Id : " + std::to_string(chatReq->_actorKey) + "���� �޼��� : " + chatReq->_str;
	Logger::getInstance()->log(Logger::Level::DEBUG, chatStr);
}