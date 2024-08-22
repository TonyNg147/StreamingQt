
#include "videoframeprocessor.h"
#include <QPainter>
VideoFrameProcessor::VideoFrameProcessor(QObject *parent)
	: QQuickPaintedItem{}
{

}

VideoSourcePool *VideoFrameProcessor::sourcePool() const
{
	return m_sourcePool;
}

void VideoFrameProcessor::setSourcePool(VideoSourcePool *newSourcePool)
{
	if (m_sourcePool == newSourcePool)
		return;
	if (m_sourcePool) QObject::disconnect(m_sourcePool, nullptr, this, nullptr);

	m_sourcePool = newSourcePool;

	QObject::connect(m_sourcePool, &VideoSourcePool::imageFrameChanged, this, &VideoFrameProcessor::onVideoFrameChanged, Qt::QueuedConnection);
	emit sourcePoolChanged();
}


void VideoFrameProcessor::paint(QPainter *painter)
{
	QRectF rect{0,0,width(),height()};
	painter->drawImage(rect, m_currentVideoFrame);
}

void VideoFrameProcessor::onVideoFrameChanged(const QImage & videoImage)
{
	m_currentVideoFrame = videoImage;
	update();
}
