
#include "cameraframeprocessor.h"
#include <QPainter>
CameraFrameProcessor::CameraFrameProcessor(QObject *parent)
	: QQuickPaintedItem{}
{

}

CameraPool *CameraFrameProcessor::sourcePool() const
{
	return m_sourcePool;
}

void CameraFrameProcessor::setSourcePool(CameraPool *newSourcePool)
{
	if (m_sourcePool == newSourcePool)
		return;
	if (m_sourcePool) QObject::disconnect(m_sourcePool, nullptr, this, nullptr);

	m_sourcePool = newSourcePool;

	QObject::connect(m_sourcePool, &CameraPool::videoFrameChanged, this, &CameraFrameProcessor::onVideoFrameChanged, Qt::QueuedConnection);
	emit sourcePoolChanged();
}


void CameraFrameProcessor::paint(QPainter *painter)
{
	QRectF rect{0,0,width(),height()};
	painter->drawImage(rect, m_currentVideoFrame);
}

void CameraFrameProcessor::onVideoFrameChanged(const QImage & videoImage)
{
	m_currentVideoFrame = videoImage;
	update();
}
