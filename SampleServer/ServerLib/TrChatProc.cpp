#include "TrChatProc.h"
#include "TrChat.h"
#include "Logger.h"

void TrChatReqProc::process(Tr* tr)
{
	TrChatReq* chatReq = static_cast<TrChatReq*>(tr);

	// 검증
	{
		// 뭐 스트링 그런거 하면 될듯
	}
	
	std::string chatStr = "Id : " + std::to_string(chatReq->_actorKey) + "님의 메세지 : " + chatReq->_str;
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