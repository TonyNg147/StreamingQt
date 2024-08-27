#pragma once

#include "Trackable.h"
#include "Tracker.h"
#include <IFManipulate.h>
#include <mutex>

template<typename T>
class observe_ptr : public Tracker
{
public:
	observe_ptr(T *obj)
	{
		auto lock = getLock();
		m_obj = obj;
		if (m_obj) {
			subscribe();
		}
	}

	~observe_ptr()
	{
		auto lock = getLock();
		if (m_obj) {
			unsubscribe();
		}
	}

	observe_ptr &operator=(T *obj)
	{
		if (obj) {
			if (m_obj) {
				unsubscribe();
			}
			m_obj = obj;
			subscribe();
		}
		return *this;
	}

	operator bool() const
	{
		return m_obj != nullptr;
	}

	T *operator->() const
	{
		return m_obj;
	}

	T *get() const
	{
		return m_obj;
	}

	void subscribe() override
	{
		if (m_obj == nullptr) {
			throw std::exception("Cannot subscribe. Instance must be valid.");
		}
		// auto lock = getLock();
		Trackable *trackableInstance = reinterpret_cast<Trackable *>((m_obj)->toIf(id<Trackable>()));
		if (trackableInstance == nullptr) {
			throw std::exception("The watched type must be inherited from SInterface");
		}
		trackableInstance->grantTracking(this);
	}

	void unsubscribe() override
	{
		if (m_obj == nullptr) {
			throw std::exception("Cannot unscribe. Must subscribe beforehand.");
		}
		// auto lock = getLock();
		Trackable *trackableInstance = reinterpret_cast<Trackable *>(m_obj->toIf(id<Trackable>()));
		if (trackableInstance == nullptr) {
			throw std::exception("The watched type must be inherited from SInterface");
		}
		trackableInstance->unGrantTracking(this);
		reset();
	}

private:
	void reset()
	{
		m_obj = nullptr;
	}

	std::unique_lock<std::mutex> getLock()
	{
		return std::unique_lock<std::mutex>(m_mtx);
	}

private:
	T *m_obj = nullptr;

	std::mutex m_mtx;
};
