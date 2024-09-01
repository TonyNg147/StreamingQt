#ifndef PAINTEDITEM_H
#define PAINTEDITEM_H

#include "AnchorsItem.h"
#include <functional>
#include <QQuickPaintedItem>

class PaintedItem
    : public QQuickPaintedItem
    , public AnchorItem
{
	Q_OBJECT

public:
	PaintedItem(QQuickItem *parent = nullptr);

	void setPaintedRoutine(std::function<void(QPainter *)> &&);

	void paint(QPainter *) final;

protected:
	std::function<void(QPainter *)> m_paintedRoutine;
};

#endif // PAINTEDITEM_H
