#include "TrChatProc.h"
#include "TrChat.h"
#include "Logger.h"

void TrChatReqProc::process(Tr* tr)
{
	TrChatReqPacket* chatReq = static_cast<TrChatReqPacket*>(tr);

	// 검증
	{
		// 뭐 스트링 그런거 하면 될듯
	}
	
	std::string chatStr = "Id : " + std::to_string(chatReq->_actorKey) + "님의 메세지 : " + chatReq->_str;
	Logger::getInstance()->log(Logger::Level::DEBUG, chatStr);
}