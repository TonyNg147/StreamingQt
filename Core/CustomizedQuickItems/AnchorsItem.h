#pragma once
#include <QObject>
class QQuickItem;

class AnchorItem
{
public:
	AnchorItem(QQuickItem *);

	virtual ~AnchorItem()
	{
	}

	void setFill(QQuickItem *item);
	virtual void setLeft(QObject *parent);
	virtual void setRight(QObject *parent);
	virtual void setBottom(QObject *parent);
	virtual void setTop(QObject *parent);
	virtual void setLeftMargin(const size_t &);
	virtual void setRightMargin(const size_t &);
	virtual void setTopMargin(const size_t &);
	virtual void setBottomMargin(const size_t &);
	virtual void setMargins(const size_t &);

protected:
	QObject *m_anchorsObj = nullptr;
};
