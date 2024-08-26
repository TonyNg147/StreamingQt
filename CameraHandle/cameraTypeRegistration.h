#ifndef CAMERATYPEREGISTRATION_H
#define CAMERATYPEREGISTRATION_H

#include "camerapool.h"
#include "cameraframeprocessor.h"
#include "camerautils.h"
namespace CameraHandle{
static inline void registerType() {
	qmlRegisterType<CameraPool>("CameraHandle", 1,0,"CameraPool");
	qmlRegisterType<CameraFrameProcessor>("CameraHandle", 1,0,"CameraFrameProcessor");
	qmlRegisterUncreatableMetaObject(CameraUtil::staticMetaObject, "CameraHandle", 1, 0, "CameraUtil", "This namespace provides utility to Camera");
}
};

#endif // CAMERATYPEREGISTRATION_H
