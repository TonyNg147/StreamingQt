#include "camerascreencapture.h"
#include <AnimatedPaintedItem.h>
#include <QPainter>
#include <QPainterPath>
#include <QPropertyAnimation>
#include <RoundedImage.h>

CameraScreenCapture::CameraScreenCapture(const QImage &screen, QQuickItem *parentView)
    : ScreenCapture{parentView}
    , m_screen{screen}
{
	m_roundedImage.reset(new RoundedImage(screen, this));
	m_roundedImage->setRadius(10);
	m_roundedImage->setFill(this);
	m_roundedImage->setMargins(10);

	setPaintedRoutine([this](QPainter *painter) -> void {
		QRectF rect(x(), y(), width(), height());

		QPen pen(Qt::white, 30, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
		painter->setPen(pen);

		QPainterPath path;
		path.addRoundedRect(rect, 15, 15);

		painter->drawPath(path);
	});
}

CameraScreenCapture::~CameraScreenCapture()
{
}
