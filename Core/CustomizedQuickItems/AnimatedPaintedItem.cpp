#include "AnimatedPaintedItem.h"
#include <QDebug>
#include <QPainter>

AnimatedPaintedItem::AnimatedPaintedItem(QQuickItem *parent)
    : PaintedItem{parent}
{
	m_animation.setTargetObject(this);
	setParentItem(parent);
}

AnimatedPaintedItem::~AnimatedPaintedItem()
{
}

void AnimatedPaintedItem::start()
{
	if (m_animation.startValue().isValid() || m_animation.endValue().isValid()) {
		m_animation.start();
	}
	QVariant children = property("children");
	if (children.isValid()) {
		QQmlListProperty<QQuickItem> childrenItem = children.value<QQmlListProperty<QQuickItem>>();
		const qsizetype count = childrenItem.count(&childrenItem);
		for (qsizetype i = 0; i < count; ++i) {
			AnimatedPaintedItem *animatedItem = dynamic_cast<AnimatedPaintedItem *>(
			    childrenItem.at(&childrenItem, i));
			if (animatedItem) {
				animatedItem->start();
			}
		}
	}
}

void AnimatedPaintedItem::setStartValue(const QVariant &value)
{
	m_animation.setStartValue(value);
}

void AnimatedPaintedItem::setEndValue(const QVariant &value)
{
	m_animation.setEndValue(value);
}

void AnimatedPaintedItem::setPropertyName(const QByteArray &name)
{
	m_animation.setPropertyName(name);
}

void AnimatedPaintedItem::setDuration(const int &duration)
{
	m_animation.setDuration(duration);
}
