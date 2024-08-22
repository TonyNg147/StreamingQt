#ifndef VIDEOTYPEREGISTRATION_H
#define VIDEOTYPEREGISTRATION_H

#include "videoframeprocessor.h"
#include "videosourcepool.h"
namespace CustomVideo{
static inline void registerType() {
	qmlRegisterType<VideoSourcePool>("CustomVideoHandle", 1,0,"VideoSourcePool");
	qmlRegisterType<VideoFrameProcessor>("CustomVideoHandle", 1,0,"VideoFrameProcessor");
}
};

#endif // VIDEOTYPEREGISTRATION_H
