#pragma once
#include "Contents.h"

class Tr;
class Actor;
class NetworkContents : public Contents
{
public:
	NetworkContents();
	virtual ~NetworkContents();

public:
	virtual const ContentsType getType() { return ContentsType::eNetwork; };
	virtual void recvTr(Tr* tr) = 0;
};