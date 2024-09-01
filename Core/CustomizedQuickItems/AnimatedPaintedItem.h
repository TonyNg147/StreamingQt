#pragma once

#include "AnchorsItem.h"
#include "painteditem.h"
#include <QPropertyAnimation>
#include <QQuickPaintedItem>

class AnimatedPaintedItem : public PaintedItem
{
	Q_OBJECT

public:
	AnimatedPaintedItem(QQuickItem *parent = nullptr);

	~AnimatedPaintedItem();

	virtual void start();

	void setStartValue(const QVariant &);

	void setEndValue(const QVariant &);

	void setPropertyName(const QByteArray &);

	void setDuration(const int &);

private:
	// I choose the composition approach at this point instead of inheritance
	// because both QPropertyAnimation and QQuickItem are inherited from QObject
	// leading to ambiguousity when we try to refer QOject properties as well as functionalties
	QPropertyAnimation m_animation;
};
