#include "TrChatProc.h"
#include "TrChat.h"
#include "Logger.h"

void TrChatReqProc::process(Tr* tr)
{
	TrChatReq* chatReq = static_cast<TrChatReq*>(tr);

	// ����
	{
		// �� ��Ʈ�� �׷��� �ϸ� �ɵ�
	}
	
	std::string chatStr = "Id : " + std::to_string(chatReq->_actorKey) + "���� �޼��� : " + chatReq->_str;
	Logger::getInstance()->log(Logger::Level::DEBUG, chatStr);


	bool tester = false;

	while (true)
	{
		int num = 0;
		++num;

		if (true == tester)
		{
			break;
		}
	}
}