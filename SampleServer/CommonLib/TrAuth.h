#pragma once
#include "Tr.h"
#include "Base.h"
#include <string.h>

#pragma pack(push, 1)    // 1바이트 크기로 정렬 byte padding
class TrNetworkConnectReq : public Tr
{
public:
	TrNetworkConnectReq() : Tr(TrId::TrNetworkConnectReq, ThreadType::eContents, sizeof(TrNetworkConnectReq)) {}
	~TrNetworkConnectReq() {}

	void set(const char* name)
	{
		// 검증을 넣는다.
		strcpy_s(_name, name);
	}
public:
	char _name[60] = {};
	Session_ID _sessionId = undefinedSessionId;	// 이친구만 서버에서 채워진다. 구현의 편리를 위해서
};
#pragma pack(pop)

#pragma pack(push, 1)    // 1바이트 크기로 정렬 byte padding
class TrNetworkConnectAck : public Tr
{
public:
	TrNetworkConnectAck() : Tr(TrId::TrNetworkConnectAck, ThreadType::eClient, sizeof(TrNetworkConnectAck)) {}
	~TrNetworkConnectAck() {}

	void set(const ActorKey& actorKey)
	{
		// 검증을 넣는다.
		_actorKey = actorKey;
	}
public:
	ActorKey _actorKey = undefinedActorKey;
};
#pragma pack(pop)

#pragma pack(push, 1)    // 1바이트 크기로 정렬 byte padding
class TrNetworkDisConnectReq : public Tr
{
public:
	TrNetworkDisConnectReq() : Tr(TrId::TrNetworkDisConnectReq, ThreadType::eContents, sizeof(TrNetworkDisConnectReq)) {}
	~TrNetworkDisConnectReq() {}

	void set(const Session_ID& sessionId)
	{
		// 검증을 넣는다.
		_sessionId = sessionId;
	}
public:
	Session_ID _sessionId = undefinedSessionId;
};
#pragma pack(pop)


#pragma pack(push, 1)    // 1바이트 크기로 정렬 byte padding
class TrActorLoginAck : public Tr
{
public:
	TrActorLoginAck() : Tr(TrId::TrActorLoginAck, ThreadType::eClient, sizeof(TrActorLoginAck)) {}
	~TrActorLoginAck() {}

	void set(const ActorKey& actorKey, const char* name)
	{
		// 검증을 넣는다.
		_actorKey = actorKey;
		strcpy_s(_name, name);
	}
public:
	ActorKey _actorKey = undefinedActorKey;
	char _name[60] = {};
};
#pragma pack(pop)