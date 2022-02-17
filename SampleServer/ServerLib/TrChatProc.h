#pragma once
#include "Proc.h"

class Tr;

class TrChatReqProc : public Proc
{
public: 
	TrChatReqProc() : Proc(TrId::eTrChatReq) {	}
	virtual ~TrChatReqProc() {}

public:
	virtual void process(Tr* tr);
};
