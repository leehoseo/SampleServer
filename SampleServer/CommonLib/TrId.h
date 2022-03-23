#pragma once

// Req : 클라이언트에서 서버로 요청
// Ack : 서버에서 클라이언트로 응답
enum class TrId
{
	TrChatReq = 0,
	TrChatAck,
	TrNetworkConnectReq,
	TrNetworkConnectAck,
	TrNetworkDisConnectReq,
	TrActorLoginReq,
	TrActorLoginAck,
	Count,
};