#pragma once
#include "Trackable.h"
#include <list>
#include <mutex>

class TrackableImpl : public Trackable
{
public:
	~TrackableImpl() override;
	void grantTracking(Tracker *) final;
	void unGrantTracking(Tracker *) final;

	void *toIf(const IFRepresent &ifRepresent) override
	{
		if (ifRepresent == id<Trackable>()) {
			return static_cast<Trackable *>(this);
		}
		return nullptr;
	}

private:
	std::list<Tracker *> m_trackers;
	std::mutex m_mtx;
};
