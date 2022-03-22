#pragma once
#include "Tr.h"
#include "Base.h"
#include <string.h>

#pragma pack(push, 1)    // 1����Ʈ ũ��� ���� byte padding
class TrNetworkConnectReq : public Tr
{
public:
	TrNetworkConnectReq() : Tr(TrId::TrNetworkConnectReq, ThreadType::eContents, sizeof(TrNetworkConnectReq)) {}
	~TrNetworkConnectReq() {}

	void set(const char* name)
	{
		// ������ �ִ´�.
		strcpy_s(_name, name);
	}
public:
	char _name[60] = {};
	Session_ID _sessionId = undefinedSessionId;	// ��ģ���� �������� ä������. ������ ���� ���ؼ�
};
#pragma pack(pop)

#pragma pack(push, 1)    // 1����Ʈ ũ��� ���� byte padding
class TrNetworkConnectAck : public Tr
{
public:
	TrNetworkConnectAck() : Tr(TrId::TrNetworkConnectAck, ThreadType::eCount, sizeof(TrNetworkConnectAck)) {}
	~TrNetworkConnectAck() {}

	void set(const ActorKey& actorKey)
	{
		// ������ �ִ´�.
		_actorKey = actorKey;
	}
public:
	ActorKey _actorKey = undefinedActorKey;
};
#pragma pack(pop)


#pragma pack(push, 1)    // 1����Ʈ ũ��� ���� byte padding
class TrActorLoginAck : public Tr
{
public:
	TrActorLoginAck() : Tr(TrId::TrActorLoginAck, ThreadType::eCount, sizeof(TrActorLoginAck)) {}
	~TrActorLoginAck() {}

	void set(const ActorKey& actorKey, const char* name)
	{
		// ������ �ִ´�.
		_actorKey = actorKey;
		strcpy_s(_name, name);
	}
public:
	ActorKey _actorKey = undefinedActorKey;
	char _name[60] = {};
};
#pragma pack(pop)