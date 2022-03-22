#pragma once
#include "Proc.h"

class Tr;
class TrNetworkConnectReqProc : public Proc
{
public:
	TrNetworkConnectReqProc() : Proc() {}
	virtual ~TrNetworkConnectReqProc() {}

public:
	virtual void process(Tr* tr);
};