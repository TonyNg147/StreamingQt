#ifndef FRAME_SOURCE_BASE_H
#define FRAME_SOURCE_BASE_H
#include <DeleteLater.h>
#include <QImage>
#include <QObject>
#include <QThread>
#include <QVideoFrame>

class FrameSourceBase : public QObject
{
	Q_OBJECT

public:
	FrameSourceBase(QObject *parent = nullptr)
	    : QObject{parent}
	{
	}

public slots:
	virtual void start() = 0;
	virtual void stop() = 0;
signals:
	void frameChanged(const QImage &);
	void frameChanged(const QVideoFrame &);

protected:
	QThread m_processingThread;
};

#endif
