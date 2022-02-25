#include "Tr.h"

Tr::Tr()
{
}


Tr::Tr(const TrId trId, const ThreadType type, const int maxSize)
	: _type(type)
	, _maxSize(maxSize)
	, _trId(trId)
{
}

Tr::~Tr()
{
}
