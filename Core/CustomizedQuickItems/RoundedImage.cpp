#include "RoundedImage.h"
#include <QPainter>
#include <QPainterPath>

RoundedImageBase::RoundedImageBase(const QImage &image)
    : m_image{image}
{
}

RoundedImageBase::~RoundedImageBase()
{
}

void RoundedImageBase::setRadius(const size_t &radius)
{
	m_radius = radius;
}

size_t RoundedImageBase::radius() const
{
	return m_radius;
}

QImage RoundedImageBase::image() const
{
	return m_image;
}

void RoundedImageBase::setImage(const QImage &image)
{
	m_image = image;
}

RoundedImage::RoundedImage(const QImage &image, QQuickItem *parent)
    : PaintedItem{parent}
    , RoundedImageBase{image}

{
	setPaintedRoutine([this](QPainter *painter) {
		QRectF rect(x(), y(), width(), height());
		QPainterPath path;
		path.addRoundedRect(rect, m_radius, m_radius);
		painter->setClipPath(path);
		painter->drawImage(rect, m_image);
	});
}

RoundedImage::~RoundedImage()
{
}

AnimatedRoundedImage::AnimatedRoundedImage(const QImage &image, QQuickItem *parent)
    : AnimatedPaintedItem{parent}
    , RoundedImageBase{image}

{
	setPaintedRoutine([this](QPainter *painter) {
		QRectF rect(x(), y(), width(), height());
		QPainterPath path;
		path.addRoundedRect(rect, m_radius, m_radius);
		painter->setClipPath(path);
		painter->drawImage(rect, m_image);
	});
}

AnimatedRoundedImage::~AnimatedRoundedImage()
{
}
