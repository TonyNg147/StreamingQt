#ifndef VIDEO_STORAGE_BASE_H
#define VIDEO_STORAGE_BASE_H
#include "RecordingBase.h"

class QMediaCaptureSession;

class VideoRecordingBase : public RecordingBase
{
	Q_OBJECT

public:
	VideoRecordingBase(QObject *parent = nullptr);
	~VideoRecordingBase() override;

public slots:

	virtual void attachToScreenCapture(QMediaCaptureSession *) = 0;

	virtual void detachFromCurrent() = 0;

signals:
	void attachStatusOnCaptureSessionChanged(bool);

protected:
	QMediaCaptureSession *m_screenCaptureSession;
};

#endif
