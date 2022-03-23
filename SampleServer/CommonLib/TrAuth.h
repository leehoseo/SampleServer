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
	void set() { } // 규칙성을 위해 넣어준다.
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
	ActorKey _actorKey;
};
#pragma pack(pop)

#pragma pack(push, 1)    // 1바이트 크기로 정렬 byte padding
class TrNetworkDisConnectReq : public Tr
{
public:
	TrNetworkDisConnectReq() : Tr(TrId::TrNetworkDisConnectReq, ThreadType::eContents, sizeof(TrNetworkDisConnectReq)) {}
	~TrNetworkDisConnectReq() {}

	void set(const SessionKey& sessionKey)
	{
		// 검증을 넣는다.
		_sessionKey = sessionKey;
	}
public:
	SessionKey _sessionKey;
};
#pragma pack(pop)

#pragma pack(push, 1)    // 1바이트 크기로 정렬 byte padding
class TrActorLoginReq : public Tr
{
public:
	TrActorLoginReq() : Tr(TrId::TrActorLoginReq, ThreadType::eContents, sizeof(TrActorLoginReq)) {}
	~TrActorLoginReq() {}

	void set(const char* name)
	{
		// 검증을 넣는다.
		strcpy_s(_name, name);
	}
public:
	char _name[60] = {};
};
#pragma pack(pop)

#pragma pack(push, 1)    // 1바이트 크기로 정렬 byte padding
class TrActorLoginAck : public Tr
{
public:
	TrActorLoginAck() : Tr(TrId::TrActorLoginAck, ThreadType::eClient, sizeof(TrActorLoginAck)) {}
	~TrActorLoginAck() {}

	void set(const ActorKey& actorKey, const char* name, const bool isSelfPlayer)
	{
		// 검증을 넣는다.
		_actorKey = actorKey;
		strcpy_s(_name, name);
		_isSelfPlayer = isSelfPlayer;
	}
public:
	ActorKey _actorKey;
	char _name[60] = {};
	bool _isSelfPlayer = false;
};
#pragma pack(pop)