#include "TrChatProc.h"
#include "TrChat.h"
#include "Logger.h"
#include <chrono>
#include <thread>

void TrChatReqProc::process(Tr* tr)
{
	TrChatReq* chatReq = static_cast<TrChatReq*>(tr);

	// ����
	{
		// �� ��Ʈ�� �׷��� �ϸ� �ɵ�
	}
	
	std::string chatStr = "Id : " + std::to_string(chatReq->_actorKey) + "���� �޼��� : " + chatReq->_str;
	Logger::getInstance()->log(Logger::Level::DEBUG, chatStr);
}