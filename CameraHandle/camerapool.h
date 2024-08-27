#ifndef CAMERASOURCEPOOL_H
#define CAMERASOURCEPOOL_H

#include <QObject>

#include <QScopedPointer>
#include <QThread>

#include "camerautils.h"
#include <capturesession.h>
#include <executionhelper.h>
#include <FrameSourceBase.h>
#include <QMediaCaptureSession>
class CameraPoolImpl;

class CameraPool
    : public FrameSourceBase
    , public ExecutionHelper
{
	Q_OBJECT
	Q_PROPERTY(
	    CameraUtil::CameraPosition position READ position WRITE setPosition NOTIFY positionChanged)
	Q_PROPERTY(const CMediaCaptureSession *captureSession READ captureSession CONSTANT)

public:
	CameraPool(QObject *parent = nullptr);
	~CameraPool() override;

	CameraUtil::CameraPosition position() const;
	void setPosition(CameraUtil::CameraPosition newPosition);
	const CMediaCaptureSession *captureSession() const;

public slots:
	void stop() final;
	void start() final;

signals:
	void positionChanged();

private:
	void onVideoFrameImageRecevied(const QImage &);
	void onVideoFrameRecevied(const QVideoFrame &);

private:
	std::unique_ptr<CameraPoolImpl, DeleteLaterQObject> m_impl;
	CameraUtil::CameraPosition m_position = {CameraUtil::CameraPosition::UNKNOWN};
};

#endif // CAMERASOURCEPOOL_H
