#pragma once
#include "Contents.h"
#include "Base.h"

// ���⼭ ���ʹ� Ŭ���̾�Ʈ(�𸮾�)�� �Ⱦ��ĵ�...�׷��� ���� ����
class FieldContents : public Contents
{
public:
	FieldContents();
	virtual ~FieldContents();
	virtual const ContentsType getType() { return ContentsType::eField; };

protected:
	FieldKey _currentFieldKey;
};

