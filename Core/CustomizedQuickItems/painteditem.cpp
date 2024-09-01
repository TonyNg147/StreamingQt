#include "painteditem.h"

PaintedItem::PaintedItem(QQuickItem *parent)
    : AnchorItem{this}
{
	setParentItem(parent);
}

void PaintedItem::setPaintedRoutine(std::function<void(QPainter *)> &&paintedRoutine)
{
	if (paintedRoutine) {
		m_paintedRoutine = std::move(paintedRoutine);
	}
}

void PaintedItem::paint(QPainter *painter)
{
	if (painter) {
		if (m_paintedRoutine) {
			m_paintedRoutine(painter);
		} else {
			qFatal() << "You must specify painted Routine for this type of item";
		}
	}
}
