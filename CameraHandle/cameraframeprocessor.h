#ifndef CAMERAFRAMEPROCESSOR_H
#define CAMERAFRAMEPROCESSOR_H

#include <QObject>
#include <QQuickItem>
#include <QImage>
#include <QQuickPaintedItem>

#include "camerapool.h"

class CameraFrameProcessor : public QQuickPaintedItem
{
	Q_OBJECT
	Q_PROPERTY(CameraPool* sourcePool READ sourcePool WRITE setSourcePool NOTIFY sourcePoolChanged)
public:
	explicit CameraFrameProcessor(QObject *parent = nullptr);

	CameraPool *sourcePool() const;
	void setSourcePool(CameraPool *newSourcePool);

	void paint(QPainter *painter) final;

private:
	void onVideoFrameChanged(const QImage&);

signals:
	void sourcePoolChanged();

private:
	CameraPool *m_sourcePool = nullptr;
	QImage m_currentVideoFrame;
};

#endif // CAMERAFRAMEPROCESSOR_H
