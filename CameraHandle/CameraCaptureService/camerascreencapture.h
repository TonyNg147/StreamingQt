#ifndef CAMERASCREENCAPTURE_H
#define CAMERASCREENCAPTURE_H

#include "ScreenCapture.h"
#include <QImage>

class RoundedImage;
class AnimatedPaintedItem;

class CameraScreenCapture final : public ScreenCapture
{
public:
	CameraScreenCapture(const QImage &screen, QQuickItem *parentView);
	~CameraScreenCapture();

private:
	QImage m_screen;
	std::optional<float> m_scale;
	std::unique_ptr<RoundedImage> m_roundedImage;
	std::unique_ptr<AnimatedPaintedItem> m_splashImage;
};

#endif // CAMERASCREENCAPTURE_H
