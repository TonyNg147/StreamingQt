#include "camerapool.h"
#include <FrameSourceBaseImpl.h>
#include <QCamera>
#include <QScopedPointer>
#include <QVideoSink>

using namespace CameraUtil;

namespace {
constexpr int cNumberOfRetryStartingCamera = 3;
}

class CMediaCaptureSessionImpl : public CMediaCaptureSession
{
public:
	QMediaCaptureSession *get() override
	{
		return &m_cameraCaptureSession;
	}

private:
	QMediaCaptureSession m_cameraCaptureSession;
};

class CameraPoolImpl : public FrameSourceBaseImpl
{
	Q_OBJECT

public:
	CameraPoolImpl(QObject *parent = nullptr);
public slots:
	void setCameraPosition(const CameraPosition &);

	void start() final;
	void stop() override;
	bool isReady() override;

	CMediaCaptureSession *getCaptureSession()
	{
		return &m_captureSession;
	}

private:
	void onFrameRecevied(const QVideoFrame &);
	void errorOccurred(QCamera::Error error, const QString &errorString);

private:
	CMediaCaptureSessionImpl m_captureSession;
	QScopedPointer<QCamera, QScopedPointerDeleteLater> m_camera;
	QScopedPointer<QVideoSink, QScopedPointerDeleteLater> m_videoSink;
	CameraUtil::CameraPosition m_position = CameraPosition::UNKNOWN;
};

CameraPool::CameraPool(QObject *parent)
    : FrameSourceBase{parent}
{
	m_impl.reset(new CameraPoolImpl);
	m_impl->moveToThread(&m_processingThread);
	QObject::connect(
	    m_impl.get(),
	    qOverload<const QImage &>(&CameraPoolImpl::frameChanged),
	    this,
	    &CameraPool::onVideoFrameImageRecevied,
	    Qt::QueuedConnection);
	QObject::connect(
	    m_impl.get(),
	    qOverload<const QVideoFrame &>(&CameraPoolImpl::frameChanged),
	    this,
	    &CameraPool::onVideoFrameRecevied,
	    Qt::QueuedConnection);
	m_processingThread.start();
}

CameraPool::~CameraPool()
{
	m_processingThread.quit();
	m_processingThread.wait();
}

CameraUtil::CameraPosition CameraPool::position() const
{
	return m_position;
}

void CameraPool::setPosition(CameraUtil::CameraPosition newPosition)
{
	if (m_position == newPosition) {
		return;
	}
	m_position = newPosition;
	QMetaObject::invokeMethod(
	    m_impl.get(), "setCameraPosition", Q_ARG(CameraUtil::CameraPosition, newPosition));
	emit positionChanged();
}

void CameraPool::stop()
{
}

void CameraPool::start()
{
	auto startWhenCameraReadyFn = [this]() {
		m_impl->start();
	};

	auto conditionForStartFn = [this]() -> bool {
		return m_impl->isReady();
	};

	execOnlyCondMetOrRetry(std::move(startWhenCameraReadyFn), std::move(conditionForStartFn), 5);
}

void CameraPool::onVideoFrameImageRecevied(const QImage &imageFrame)
{
	emit frameChanged(imageFrame);
}

void CameraPool::onVideoFrameRecevied(const QVideoFrame &videoFrame)
{
	emit frameChanged(videoFrame);
}

CameraPoolImpl::CameraPoolImpl(QObject *parent)
    : FrameSourceBaseImpl{parent}
    , m_videoSink{new QVideoSink}
{
	m_captureSession.get()->setVideoSink(m_videoSink.get());
	QObject::connect(
	    m_videoSink.get(), &QVideoSink::videoFrameChanged, this, &CameraPoolImpl::onFrameRecevied);
}

void CameraPoolImpl::setCameraPosition(const CameraPosition &position)
{
	if (m_position == position) {
		return;
	}
	m_position = position;

	const QCameraDevice::Position cameraPosition = CameraUtil::fromUtilCameraPosition(m_position);
	// The position decides the type of the camera, so we need to reset camera at this point.
	m_camera.reset(new QCamera(cameraPosition));

	QObject::connect(m_camera.get(), &QCamera::errorOccurred, this, &CameraPoolImpl::errorOccurred);

	m_captureSession.get()->setCamera(m_camera.get());
}

bool CameraPoolImpl::isReady()
{
	return m_camera && m_camera->isAvailable();
}

void CameraPoolImpl::start()
{
	m_camera->start();
}

void CameraPoolImpl::stop()
{
}

const CMediaCaptureSession *CameraPool::captureSession() const
{
	return m_impl->getCaptureSession();
}

void CameraPoolImpl::onFrameRecevied(const QVideoFrame &videoFrame)
{
	QVideoFrame frame(videoFrame);
	if (frame.map(QVideoFrame::ReadOnly)) {
		frame.unmap();
	}
	emit frameChanged(videoFrame.toImage());
	emit frameChanged(videoFrame);
}

void CameraPoolImpl::errorOccurred(QCamera::Error error, const QString &errorString)
{
	qWarning() << "Error of the camera " << error << " " << errorString;
}

#include <camerapool.moc>
