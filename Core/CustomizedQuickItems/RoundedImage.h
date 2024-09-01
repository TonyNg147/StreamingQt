#pragma once

#include "AnimatedPaintedItem.h"
#include "PaintedItem.h"
#include <QImage>

class RoundedImageBase
{
public:
	RoundedImageBase(const QImage & = QImage());

	virtual ~RoundedImageBase();

	virtual void setRadius(const size_t &);

	virtual size_t radius() const;

	virtual QImage image() const;

	virtual void setImage(const QImage &);

protected:
	QImage m_image;

	size_t m_radius = 0;
};

class RoundedImage
    : public PaintedItem
    , public RoundedImageBase
{
	Q_OBJECT

public:
	RoundedImage(const QImage & = QImage(), QQuickItem *parent = nullptr);

	~RoundedImage();
};

class AnimatedRoundedImage
    : public AnimatedPaintedItem
    , public RoundedImageBase
{
	Q_OBJECT

public:
	AnimatedRoundedImage(const QImage & = QImage(), QQuickItem *parent = nullptr);

	~AnimatedRoundedImage();
};
