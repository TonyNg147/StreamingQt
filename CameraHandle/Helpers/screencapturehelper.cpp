#include "screencapturehelper.h"
#include "animationhelper.h"
#include <camerascreencapture.h>
#include <QDebug>

ScreenCaptureHelper &ScreenCaptureHelper::getInstance()
{
	static ScreenCaptureHelper instance;
	return instance;
}

std::unique_ptr<ScreenCapture> ScreenCaptureHelper::makeCameraScreenCapture(
    const QImage &image, QQuickItem *quickItem)
{
	if (quickItem) {
		std::unique_ptr<ScreenCapture> screenCapture = std::make_unique<CameraScreenCapture>(
		    image, quickItem);
		screenCapture->setPropertyName("scale");
		screenCapture->setTransformOrigin(QQuickItem::BottomRight);
		screenCapture->setFill(quickItem);
		screenCapture->setEndValue(QVariant(0.3));

		AnimationHelper::getInstance().attachAnimation(screenCapture.get(), AnimationType::Splash);
		return std::move(screenCapture);
	} else {
		qFatal() << "The screen capture need to be attached with a valid quickitem";
		return nullptr;
	}
}
