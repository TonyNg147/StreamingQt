#pragma once
#include <IFManipulate.h>
class Trackable;

class Tracker
{
public:
	virtual ~Tracker()
	{
	}

	virtual void subscribe() = 0;
	virtual void unsubscribe() = 0;
};
