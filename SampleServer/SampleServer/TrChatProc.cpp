#include "TrChatProc.h"
#include "TrChat.h"
#include "Logger.h"
#include <chrono>
#include <thread>

MAKE_PROCESS(TrChatReq)
{
	TrChatReq* chatReq = static_cast<TrChatReq*>(tr);

	// 검증
	{
		// 뭐 스트링 그런거 하면 될듯
	}
	
	std::string chatStr = "Id : " + std::to_string(chatReq->_actorKey) + "님의 메세지 : " + chatReq->_str;
	Logger::getInstance()->log(Logger::Level::DEBUG, chatStr);
}