#include "camerautils.h"
#include <QMediaDevices>
#include <QCameraDevice>
using namespace CameraUtil;

namespace CameraUtil{
	bool cameraAvailable() {
		return QMediaDevices::videoInputs().count() > 0;
	}

	QList<QString> camerasDescription()  {
		QList<QString> cameraDescriptions = {};
		const QList<QCameraDevice> cameras = QMediaDevices::videoInputs();
		for (const QCameraDevice &cameraDevice : cameras) {
			cameraDescriptions << cameraDevice.description();
		}
		return cameraDescriptions;
	}

	CameraPosition toUtilCameraPosition(const QCameraDevice::Position& position) {
		switch(position) {
		case QCameraDevice::UnspecifiedPosition: return CameraPosition::UNSPECIFIED;
		case QCameraDevice::BackFace: return CameraPosition::REAR;
		case QCameraDevice::FrontFace: return CameraPosition::FRONT;
		default:return CameraPosition::UNKNOWN;
		}
	}

	QCameraDevice::Position fromUtilCameraPosition(const CameraPosition& position) {
		switch(position) {
		case CameraPosition::UNSPECIFIED: return QCameraDevice::UnspecifiedPosition;
		case CameraPosition::REAR: return QCameraDevice::BackFace;
		case CameraPosition::FRONT: return QCameraDevice::FrontFace;
		default:return QCameraDevice::UnspecifiedPosition;
		}
	}
};

