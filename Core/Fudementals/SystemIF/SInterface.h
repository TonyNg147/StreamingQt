#pragma once
#include "IFRepresent.h"

class SInteface
{
public:
	virtual ~SInteface();
	virtual void *toIf(const IFRepresent &) = 0;
	virtual void reference();
	virtual void dereference();
	virtual size_t totalRefs() const;

protected:
	size_t m_count = 0;
};
