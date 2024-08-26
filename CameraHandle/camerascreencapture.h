#ifndef CAMERASCREENCAPTURE_H
#define CAMERASCREENCAPTURE_H

#include <QQuickPaintedItem>
#include <QImage>

class CameraScreenCapture : public QQuickPaintedItem
{
public:
	CameraScreenCapture(const QImage& screen, QQuickItem* parentView);
	void paint(QPainter *painter) final;
	CameraScreenCapture& setDuration(const size_t&);
	CameraScreenCapture& setOriginalPos(const QPoint&);
	CameraScreenCapture* setFinalPos(const QPoint&);
	CameraScreenCapture* setScale(const float&);
	void startAnimation();
private:
	QImage m_screen;
	size_t m_duration;
	std::optional<QPoint> m_originalPos;
	std::optional<QPoint> m_FinalPos;
	std::optional<float> m_scale;
};

#endif // CAMERASCREENCAPTURE_H
