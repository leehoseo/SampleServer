#pragma once
#include "FieldContents.h"

class TrLoginToLobbyReq;
class ServerFieldContents : public FieldContents
{
public:
	ServerFieldContents();
	virtual ~ServerFieldContents();

public:
	void responseTrLoginToLobbyReq(TrLoginToLobbyReq* req);
};

