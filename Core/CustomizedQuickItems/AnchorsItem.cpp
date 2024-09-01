#include "AnchorsItem.h"
#include <QDebug>
#include <QQuickItem>
#include <QVariant>

AnchorItem::AnchorItem(QQuickItem *represent)
{
	if (represent) {
		QVariant anchorsVar = represent->property("anchors");
		if (anchorsVar.isValid()) {
			m_anchorsObj = anchorsVar.value<QObject *>();
		} else {
			qFatal("The inheritant of this class must be derived from QQuickItem");
		}
	}
}

void AnchorItem::setLeft(QObject *item)
{
	if (item) {
		m_anchorsObj->setProperty("left", QVariant::fromValue(item));
	} else {
		qCritical() << "Pass invalid item for left anchors";
	}
}

void AnchorItem::setRight(QObject *item)
{
	if (item) {
		m_anchorsObj->setProperty("right", QVariant::fromValue(item));
	} else {
		qCritical() << "Pass invalid item for right anchors";
	}
}

void AnchorItem::setBottom(QObject *item)
{
	if (item) {
		m_anchorsObj->setProperty("bottom", QVariant::fromValue(item));
	} else {
		qCritical() << "Pass invalid item for bottom anchors";
	}
}

void AnchorItem::setTop(QObject *item)
{
	if (item) {
		m_anchorsObj->setProperty("top", QVariant::fromValue(item));
	} else {
		qCritical() << "Pass invalid item for top anchors";
	}
}

void AnchorItem::setFill(QQuickItem *item)
{
	if (item) {
		m_anchorsObj->setProperty("fill", QVariant::fromValue(item));
	} else {
		qCritical() << "Pass invalid item for fill anchors";
	}
}

void AnchorItem::setLeftMargin(const size_t &leftMargin)
{
	m_anchorsObj->setProperty("leftMargin", leftMargin);
}

void AnchorItem::setRightMargin(const size_t &rightMargin)
{
	m_anchorsObj->setProperty("rightMargin", rightMargin);
}

void AnchorItem::setTopMargin(const size_t &topMargin)
{
	m_anchorsObj->setProperty("topMargin", topMargin);
}

void AnchorItem::setBottomMargin(const size_t &bottomMargin)
{
	m_anchorsObj->setProperty("bottomMargin", bottomMargin);
}

void AnchorItem::setMargins(const size_t &margins)
{
	m_anchorsObj->setProperty("margins", margins);
}
