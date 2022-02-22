#pragma once
#include "Tr.h"
#include <string.h>

#pragma pack(push, 1)    // 1����Ʈ ũ��� ���� byte padding
class TrChatReqPacket : public Tr
{
public:
	TrChatReqPacket() : Tr( TrId::TrChatReq, TrType::eContents , sizeof(TrChatReqPacket))	{}
	~TrChatReqPacket() {}

	void set(const int actorKey , const char* str)
	{
		// ������ �ִ´�.
		_actorKey = actorKey;
		strcpy_s(_str, str);
	}
public:
	int	 _actorKey = 0;
	char _str[60] = {};
};
#pragma pack(pop)