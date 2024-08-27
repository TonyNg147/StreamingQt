#include "TrackableImpl.h"
#include "Tracker.h"

TrackableImpl::~TrackableImpl()
{
	// Because when unsubscribe tracker, it will call the unGrantTracking
	// leading to the mismatch between them. So i made a copy to prevent thing from happening
	auto trackers = m_trackers;
	for (auto &tracker : trackers) {
		tracker->unsubscribe();
	}
}

void TrackableImpl::grantTracking(Tracker *newTracker)
{
	if (newTracker) {
		bool isExist = false;
		for (auto &tracker : m_trackers) {
			if (tracker == newTracker) {
				isExist = true;
				break;
			}
		}
		if (!isExist) {
			std::unique_lock<std::mutex> lock(m_mtx);
			m_trackers.emplace_back(newTracker);
		}
	}
}

void TrackableImpl::unGrantTracking(Tracker *newTracker)
{
	for (auto it = m_trackers.begin(); it != m_trackers.end(); ++it) {
		if (*it == newTracker) {
			std::unique_lock<std::mutex> lock(m_mtx);
			m_trackers.erase(it);
			break;
		}
	}
}
