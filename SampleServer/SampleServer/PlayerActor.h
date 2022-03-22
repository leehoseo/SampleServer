#pragma once
#include "CharacterActor.h"
#include "Base.h"
#include <string>

class PlayerActor : public CharacterActor
{
public:
	PlayerActor();
	virtual ~PlayerActor();

	const Session_ID& getSessionId();
	void			  setSessionId(const Session_ID& sessionId);


public:
	// ������ �ʱ�ȭ �Ǵ� �����ö�
	virtual void init();

	// �ı��ɶ�
	virtual void release();

	// pop
	virtual void active();

	// push
	virtual void deactive();


private:
	Session_ID _sessionId = undefinedSessionId;
};

