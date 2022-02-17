#include "Tr.h"

Tr::Tr()
{
}


Tr::Tr(const TrId trId, const ThreadType threadType, const int maxSize)
	: _threadType(threadType)
	, _maxSize(maxSize)
	, _trId(trId)
{
}

Tr::~Tr()
{
}
