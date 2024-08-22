#include "camerapool.h"
#include <QMediaCaptureSession>
#include <QVideoSink>
#include <QCamera>
#include <QScopedPointer>

using namespace CameraUtil;

class CameraPoolImpl: public QObject{
	Q_OBJECT
public:
	CameraPoolImpl(QObject* parent = nullptr);
	void setCameraPosition(const CameraPosition&);

	bool isReadyToStream();

	void play();
private:
	void onVideoFrameReceived(const QVideoFrame&);
signals:
	void videoFrameImageChanged(const QImage&);
private:
	QMediaCaptureSession m_cameraCaptureSession;
	QScopedPointer<QCamera,QScopedPointerDeleteLater> m_camera;
	QScopedPointer<QVideoSink,QScopedPointerDeleteLater> m_videoSink;
	CameraUtil::CameraPosition m_position = CameraPosition::UNKNOWN;
};

CameraPool::CameraPool(QObject *parent)
	:QObject{parent}
	,m_impl{new CameraPoolImpl}
{
	m_impl->moveToThread(&m_workingThread);
	QObject::connect(m_impl.get(), &CameraPoolImpl::videoFrameImageChanged, this, &CameraPool::onVideoFrameImageRecevied, Qt::QueuedConnection);
	m_workingThread.start();

}

CameraPool::~CameraPool()
{
	m_workingThread.quit();
	m_workingThread.wait();
}

CameraUtil::CameraPosition CameraPool::position() const
{
	return m_position;
}

void CameraPool::setPosition(CameraUtil::CameraPosition newPosition)
{
	if (m_position == newPosition)
		return;
	m_position = newPosition;
	m_impl->setCameraPosition(newPosition);
	emit positionChanged();
}

void CameraPool::startStreaming()
{
	Q_ASSERT_X(m_impl->isReadyToStream(), "Camera Ready", "Camera must be ready before it can be used");

	m_impl->play();
}

void CameraPool::onVideoFrameImageRecevied(const QImage & imageFrame)
{
	emit videoFrameChanged(imageFrame);
}



CameraPoolImpl::CameraPoolImpl(QObject *parent)
	:QObject{parent}
	,m_cameraCaptureSession{this}
	,m_videoSink{new QVideoSink}
{
	m_cameraCaptureSession.setVideoSink(m_videoSink.get());
	QObject::connect(m_videoSink.get(), &QVideoSink::videoFrameChanged, this, &CameraPoolImpl::onVideoFrameReceived);
}

void CameraPoolImpl::setCameraPosition(const CameraPosition & position)
{
	if (m_position == position) return;
	m_position = position;

	const QCameraDevice::Position cameraPosition =  CameraUtil::fromUtilCameraPosition(m_position);

	// The position decides the type of the camera, so we need to reset camera at this point.
	m_camera.reset(new QCamera(cameraPosition));

	m_cameraCaptureSession.setCamera(m_camera.get());


}

bool CameraPoolImpl::isReadyToStream()
{
	return m_camera && m_camera->isAvailable();
}

void CameraPoolImpl::play()
{
	m_camera->start();
}

void CameraPoolImpl::onVideoFrameReceived(const QVideoFrame &videoFrame)
{
	emit videoFrameImageChanged(videoFrame.toImage());
}

#include <camerapool.moc>
