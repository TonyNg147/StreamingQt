#ifndef CAMERASOURCEPOOL_H
#define CAMERASOURCEPOOL_H

#include <QObject>

#include <QScopedPointer>
#include <QThread>


#include "camerautils.h"

class CameraPoolImpl;

class CameraPool: public QObject{
	Q_OBJECT
	Q_PROPERTY(CameraUtil::CameraPosition position READ position WRITE setPosition NOTIFY positionChanged)


public:
	CameraPool(QObject* parent = nullptr);
	~CameraPool() override;

	CameraUtil::CameraPosition position() const;
	void setPosition(CameraUtil::CameraPosition newPosition);

public slots:
	void startStreaming();



signals:
	void positionChanged();
private:
	void onVideoFrameImageRecevied(const QImage&);
signals:
	void videoFrameChanged(const QImage&);
private:
	QThread m_workingThread;
	std::unique_ptr<CameraPoolImpl> m_impl;
	CameraUtil::CameraPosition m_position = {CameraUtil::CameraPosition::UNKNOWN};
};

#endif // CAMERASOURCEPOOL_H
