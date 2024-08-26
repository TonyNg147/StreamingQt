
#include "cameraframeprocessor.h"
#include <QPainter>
#include <QPainterPath>
#include <QPropertyAnimation>



CameraFrameProcessor::CameraFrameProcessor(QObject *parent)
	: QQuickPaintedItem{}
{
	// m_screenCapture->startAnimation();
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

	QObject::connect(m_sourcePool, qOverload<const QImage&>(&CameraPool::frameChanged), this, &CameraFrameProcessor::onVideoFrameChanged, Qt::QueuedConnection);
	emit sourcePoolChanged();
}


void CameraFrameProcessor::paint(QPainter *painter)
{
	rounded(painter);
	QRectF rect{0,0,width(),height()};
	painter->drawImage(rect, m_currentVideoFrame);
}

void CameraFrameProcessor::capture()
{
	m_screenCapture.reset(new CameraScreenCapture(m_currentVideoFrame,this));
	m_screenCapture->setWidth(width());
	m_screenCapture->setHeight(height());
	m_screenCapture->setX(x());
	m_screenCapture->setY(y());
	m_screenCapture->setScale(0.3)
		->setFinalPos(QPoint(700,800));
	m_screenCapture->startAnimation();
}

void CameraFrameProcessor::onVideoFrameChanged(const QImage & videoImage)
{
	m_currentVideoFrame = videoImage;
	if (m_screenCapture){
		m_screenCapture->update();
	}
	update();
}

void CameraFrameProcessor::rounded(QPainter *painter)
{
	painter->setRenderHint(QPainter::Antialiasing);
	QPainterPath path;
	path.addRoundedRect(QRectF(0,0,width(),height()), 15,15);
	painter->fillPath(path, Qt::transparent);
	painter->drawPath(path);
	painter->setClipPath(path);
}
