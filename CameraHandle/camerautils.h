#ifndef CAMERAUTILS_H
#define CAMERAUTILS_H

#include <QObject>
#include <QList>
#include <QList>
#include <QCameraDevice>

namespace CameraUtil{
	Q_NAMESPACE
	enum class CameraPosition {
		FRONT,
		REAR,
		UNSPECIFIED,
		UNKNOWN,
	};
	Q_ENUM_NS(CameraPosition)

	bool cameraAvailable();

	QList<QString> camerasDescription();

	CameraPosition toUtilCameraPosition(const QCameraDevice::Position&);

	QCameraDevice::Position fromUtilCameraPosition(const CameraPosition&);

};

#endif // CAMERAUTILS_H
