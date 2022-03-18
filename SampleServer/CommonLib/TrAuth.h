#pragma once
#include "Tr.h"
#include <string.h>

#pragma pack(push, 1)    // 1바이트 크기로 정렬 byte padding
class TrNetworkConnectAck : public Tr
{
public:
	TrNetworkConnectAck() : Tr(TrId::TrNetworkConnectAck, ThreadType::eContents, sizeof(TrNetworkConnectAck)) {}
	~TrNetworkConnectAck() {}

	void set(const char* name)
	{
		// 검증을 넣는다.
		strcpy_s(_name, name);
	}
public:
	char _name[60] = {};
};
#pragma pack(pop)