
#include "cameraframeprocessor.h"
#include <screencapturehelper.h>

CameraFrameProcessor::CameraFrameProcessor(QObject *parent)
    : RoundedImage{}
{
}

CameraPool *CameraFrameProcessor::sourcePool() const
{
	return m_sourcePool;
}

void CameraFrameProcessor::setSourcePool(CameraPool *newSourcePool)
{
	if (m_sourcePool == newSourcePool) {
		return;
	}
	if (m_sourcePool) {
		QObject::disconnect(m_sourcePool, nullptr, this, nullptr);
	}

	m_sourcePool = newSourcePool;

	QObject::connect(
	    m_sourcePool,
	    qOverload<const QImage &>(&CameraPool::frameChanged),
	    this,
	    &CameraFrameProcessor::onVideoFrameChanged,
	    Qt::QueuedConnection);
	emit sourcePoolChanged();
}

void CameraFrameProcessor::capture()
{
	m_screenCapture = ScreenCaptureHelper::getInstance().makeCameraScreenCapture(image(), this);
	m_screenCapture->start();
}

void CameraFrameProcessor::onVideoFrameChanged(const QImage &videoImage)
{
	setImage(videoImage);
	update();
}
