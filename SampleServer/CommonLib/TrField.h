#pragma once
#include "Tr.h"
#include "Base.h"
#include <string.h>

#pragma pack(push, 1)    // 1����Ʈ ũ��� ���� byte padding
class TrLoginToLobbyReq : public Tr
{
public:
	TrLoginToLobbyReq() : Tr(TrId::TrLoginToLobbyReq, ThreadType::eContents, sizeof(TrLoginToLobbyReq)) {}
	~TrLoginToLobbyReq() {}

	void set(const ActorKey& actorKey, const char* name)
	{
		// ������ �ִ´�.
		_actorKey = actorKey;
		strcpy_s(_name, name);
	}
public:
	ActorKey _actorKey;
	char _name[60] = {};
};
#pragma pack(pop)

#pragma pack(push, 1)    // 1����Ʈ ũ��� ���� byte padding
class TrLoginToLobbyAck : public Tr
{
public:
	TrLoginToLobbyAck() : Tr(TrId::TrLoginToLobbyAck, ThreadType::eContents, sizeof(TrLoginToLobbyAck)) {}
	~TrLoginToLobbyAck() {}

	void set(const ActorKey& actorKey, const char* name)
	{
		// ������ �ִ´�.
		_actorKey = actorKey;
		strcpy_s(_name, name);
	}

public:
	ActorKey _actorKey;
	char _name[60] = {};
};
#pragma pack(pop)