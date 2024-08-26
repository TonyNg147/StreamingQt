#ifndef FRAME_SOURCE_BASE_P_H
#define FRAME_SOURCE_BASE_P_H

#include <QObject>
#include <QImage>
#include <QVideoFrame>

class FrameSourceBaseImpl: public QObject
{
    Q_OBJECT
public:
    FrameSourceBaseImpl(QObject* parent = nullptr): QObject{parent}{}
public slots:
    virtual void start() = 0;
    virtual void stop() = 0;
    virtual bool isReady() = 0;
protected:
	void onFrameRecevied(const QVideoFrame&);
signals:
    void frameChanged(const QImage&);
    void frameChanged(const QVideoFrame&);
};

#endif 
