#ifndef CAMERA_STORAGE_REGISTRATION_H
#define CAMERA_STORAGE_REGISTRATION_H

#include "camerastorage.h"
#include <QtQml/QmlTypeAndRevisionsRegistration>
namespace CameraStorageNs{
static inline void registerType() {
	qmlRegisterType<CameraStorage>("CameraStorage", 1,0,"CameraStorageInstance");
}
};

#endif // CAMERA_STORAGE_REGISTRATION_H
