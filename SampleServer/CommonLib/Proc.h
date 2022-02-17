#pragma once
#include "TrId.h"

class Tr;

class Proc
{
public:
	Proc(const TrId trId) : _trId(trId) {  };
	~Proc() {};

public:
	virtual void process(Tr* tr) = 0;

	TrId _trId;		// ��� �����忡�� ������
};

