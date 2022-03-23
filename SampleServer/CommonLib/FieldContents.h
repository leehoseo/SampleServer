#pragma once
#include "Contents.h"
#include "Base.h"

// 여기서 부터는 클라이언트(언리얼)은 안쓸탠데...그래도 여기 넣자
class FieldContents : public Contents
{
public:
	FieldContents();
	virtual ~FieldContents();
	virtual const ContentsType getType() { return ContentsType::eField; };

protected:
	FieldKey _currentFieldKey;
};

