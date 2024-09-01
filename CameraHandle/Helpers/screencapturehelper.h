#ifndef SCREENCAPTUREHELPER_H
#define SCREENCAPTUREHELPER_H
#include <memory>
#include <screenCapture.h>

class ScreenCaptureHelper
{
private:
	ScreenCaptureHelper() = default;

public:
	static ScreenCaptureHelper &getInstance();

	std::unique_ptr<ScreenCapture> makeCameraScreenCapture(const QImage &, QQuickItem *);
};

#endif // SCREENCAPTUREHELPER_H
