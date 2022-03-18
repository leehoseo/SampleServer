#pragma once
#include "CharacterActor.h"
#include "Base.h"

class PlayerActor : public CharacterActor
{
public:
	PlayerActor();
	virtual ~PlayerActor();

	const Session_ID& getSessionId();
	void			  setSessionId(const Session_ID& sessionId);

private:
	Session_ID _sessionId = undefinedSessionId;
};

