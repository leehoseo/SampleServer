#pragma once
#include "Tr.h"
#include <string.h>

#pragma pack(push, 1)    // 1����Ʈ ũ��� ���� byte padding
class TrNetworkConnectAck : public Tr
{
public:
	TrNetworkConnectAck() : Tr(TrId::TrNetworkConnectAck, ThreadType::eContents, sizeof(TrNetworkConnectAck)) {}
	~TrNetworkConnectAck() {}

	void set(const char* name)
	{
		// ������ �ִ´�.
		strcpy_s(_name, name);
	}
public:
	char _name[60] = {};
};
#pragma pack(pop)