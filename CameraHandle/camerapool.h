#ifndef CAMERASOURCEPOOL_H
#define CAMERASOURCEPOOL_H

#include <QObject>

#include <QScopedPointer>
#include <QThread>


#include "camerautils.h"
#include <FrameSourceBase.h>
#include <QMediaCaptureSession>
#include <executionhelper.h>
class CameraPoolImpl;

class CameraPool: public FrameSourceBase, public ExecutionHelper{
	Q_OBJECT
	Q_PROPERTY(CameraUtil::CameraPosition position READ position WRITE setPosition NOTIFY positionChanged)
	Q_PROPERTY(const QMediaCaptureSession* captureSession READ captureSession CONSTANT)


public:
	CameraPool(QObject* parent = nullptr);
	~CameraPool() override;

	CameraUtil::CameraPosition position() const;
	void setPosition(CameraUtil::CameraPosition newPosition);
	const QMediaCaptureSession *captureSession() const;

public slots:
	void stop() final;
	void start() final;

signals:
	void positionChanged();
private:
	void onVideoFrameImageRecevied(const QImage&);
	void onVideoFrameRecevied(const QVideoFrame&);

private:
	std::unique_ptr<CameraPoolImpl, DeleteLaterQObject> m_impl;
	CameraUtil::CameraPosition m_position = {CameraUtil::CameraPosition::UNKNOWN};
};

#endif // CAMERASOURCEPOOL_H
