#ifndef DELETE_LATER_H
#define DELETE_LATER_H
#include <QObject>

template<typename T>
struct DeleteLater
{
	void operator()(T *target)
	{
		if (target) {
			target->deleteLater();
		}
	}
};

typedef DeleteLater<QObject> DeleteLaterQObject;
#endif
