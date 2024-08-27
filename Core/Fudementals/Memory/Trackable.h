#pragma once
#include <IFManipulate.h>
class Tracker;

class Trackable : public virtual SInteface
{
public:
	virtual ~Trackable()
	{
	}

	virtual void grantTracking(Tracker *) = 0;
	virtual void unGrantTracking(Tracker *) = 0;
};

REGISTER_IF(Trackable);
