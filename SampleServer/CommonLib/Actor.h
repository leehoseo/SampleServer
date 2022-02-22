#pragma once
#include "Contents.h"
#include <unordered_map>

class Actor
{
public:
	Actor();
	~Actor();

public:
	Contents* getContents(const ContentsType& type);

protected:
	void insertContents(Contents* contents );

private:
	std::unordered_map<ContentsType, Contents*> _contentsList;
};

