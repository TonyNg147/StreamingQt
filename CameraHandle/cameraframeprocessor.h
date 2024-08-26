#ifndef CAMERAFRAMEPROCESSOR_H
#define CAMERAFRAMEPROCESSOR_H

#include <QObject>
#include <QQuickItem>
#include <QImage>
#include <QQuickPaintedItem>

#include "camerapool.h"

#include "camerascreencapture.h"

class CameraFrameProcessor : public QQuickPaintedItem
{
	Q_OBJECT
	Q_PROPERTY(CameraPool* sourcePool READ sourcePool WRITE setSourcePool NOTIFY sourcePoolChanged)
public:
	explicit CameraFrameProcessor(QObject *parent = nullptr);

	CameraPool *sourcePool() const;
	void setSourcePool(CameraPool *newSourcePool);

	void paint(QPainter *painter) final;

public slots:
	void capture();

private:
	void onVideoFrameChanged(const QImage&);
	void rounded(QPainter* painter);

signals:
	void sourcePoolChanged();

private:
	CameraPool *m_sourcePool = nullptr;
	QImage m_currentVideoFrame;
	std::unique_ptr<CameraScreenCapture> m_screenCapture;
};

#endif // CAMERAFRAMEPROCESSOR_H
