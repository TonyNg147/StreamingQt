#ifndef VIDEOFRAMEPROCESSOR_H
#define VIDEOFRAMEPROCESSOR_H

#include <QObject>
#include <QQuickItem>
#include <QImage>
#include <QQuickPaintedItem>

#include "videosourcepool.h"

class VideoFrameProcessor : public QQuickPaintedItem
{
	Q_OBJECT
	Q_PROPERTY(VideoSourcePool* sourcePool READ sourcePool WRITE setSourcePool NOTIFY sourcePoolChanged)
public:
	explicit VideoFrameProcessor(QObject *parent = nullptr);

	VideoSourcePool *sourcePool() const;
	void setSourcePool(VideoSourcePool *newSourcePool);

	void paint(QPainter *painter) final;

private:
	void onVideoFrameChanged(const QImage&);

signals:
	void sourcePoolChanged();

private:
	VideoSourcePool *m_sourcePool = nullptr;
	QImage m_currentVideoFrame;
};

#endif // VIDEOFRAMEPROCESSOR_H
