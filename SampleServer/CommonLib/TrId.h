#pragma once

// Req : Ŭ���̾�Ʈ���� ������ ��û
// Ack : �������� Ŭ���̾�Ʈ�� ����
enum class TrId
{
	TrChatReq = 0,
	TrChatAck,
	TrNetworkConnectAck,
	TrLogInReq,
	TrLogInAck,
	Count,
};