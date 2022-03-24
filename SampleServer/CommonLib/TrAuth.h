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

	// 클라이언트에서 요청했을때는 actorKey를 사용한다.
	void set(const ActorKey& actorKey)
	{
		// 검증을 넣는다.
		_actorKey = actorKey;
	}

	// 강제로 소켓 연결이 해제됐을경우 서버에서 사용한다.
	void set(const SessionKey& sessionKey)
	{
		// 검증을 넣는다.
		_sessionKey = sessionKey;
	}
public:
	ActorKey _actorKey;
	SessionKey _sessionKey;
};
#pragma pack(pop)