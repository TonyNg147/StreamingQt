#ifndef CAMERA_STORAGE_H
#define CAMERA_STORAGE_H
#include "camerastorageservice.h"
#include <DeleteLater.h>
#include <QMediaRecorder>
#include <VideoRecordingBase.h>
#include <VideoStorageBase.h>
class QMediaRecorder;

class CameraStorage
    : public VideoRecordingBase
    , public VideoStorageBase
{
	Q_OBJECT
	Q_PROPERTY(QString recordingPath WRITE setRecordingPath)

public:
	CameraStorage(QObject *parent = nullptr);
	virtual void setVideoSize(const size_t &) override;
	virtual void setNumberOfVideo(const uint8_t &) override;
	virtual void setDurationForEach(const size_t &) override;

public slots:

	virtual void attachToScreenCapture(CMediaCaptureSession *) override;

	virtual void detachFromCurrent() override;

	virtual void setRecordingPath(const QString &) override;

	virtual bool startRecording() override;

	virtual bool stopRecording() override;

private:
	virtual void stopImpl() override;

private:
	void updateStorageCapacity() override;

private:
	std::unique_ptr<QMediaRecorder> m_recorder;
	std::unique_ptr<CameraStorageServiceBase> m_cameraService;
	observe_ptr<CMediaCaptureSession> m_screenCaptureSession = nullptr;
};

#endif // CAMERA_STORAGE_H
