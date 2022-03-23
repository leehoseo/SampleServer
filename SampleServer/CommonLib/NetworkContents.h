#pragma once
#include "Contents.h"
#include "Iocp.h"
#include "BaseTime.h"

class Tr;
class Actor;
class NetworkContents : public Contents
{
public:
	NetworkContents();
	virtual ~NetworkContents();

public:
	virtual const ContentsType getType() { return ContentsType::eNetwork; };
	void recvTr(Tr* tr);
	virtual void init(Actor* owner);

	void sendToServer(Tr* tr, const TickCount64 timer);
	void recvTrEvent(Tr* tr, const TickCount64 timer);
protected:
	Iocp* _iocp = nullptr;
};