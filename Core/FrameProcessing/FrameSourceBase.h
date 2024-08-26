#ifndef FRAME_SOURCE_BASE_H
#define FRAME_SOURCE_BASE_H
#include <QObject>
#include <QImage>
#include <QVideoFrame>
#include <QThread>
#include <DeleteLater.h>

class FrameSourceBase: public QObject
{
    Q_OBJECT
public:
	FrameSourceBase(QObject* parent = nullptr): QObject{parent}{}
public slots:
    virtual void start() = 0;
    virtual void stop() = 0;
signals:
	void frameChanged(const QImage&);
	void frameChanged(const QVideoFrame&);
protected:
    QThread m_processingThread;
};

#endif 
