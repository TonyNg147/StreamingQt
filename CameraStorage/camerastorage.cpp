#include "camerastorage.h"
#include <QMediaCaptureSession>

#include "camerastorageservice.h"
#include <QUrl>

namespace {
constexpr size_t minuteToSeconds = 1000;
constexpr size_t videoDuration = 10 * minuteToSeconds;
constexpr size_t NumberOfFile = 1;
} // namespace

CameraStorage::CameraStorage(QObject *parent)
    : VideoRecordingBase{parent}
    , m_recorder{new QMediaRecorder}
    , m_cameraService{new CameraStorageService{
          videoDuration, NumberOfFile, "C:\\Users\\Tony\\Desktop\\hehe\\SavingVideoFolder\\Nguyen"}}
{
	m_cameraService->setObservant(this);
	QObject::connect(
	    m_recorder.get(),
	    &QMediaRecorder::errorOccurred,
	    this,
	    [this](QMediaRecorder::Error error, const QString &errorString) {
		    qWarning() << "error is " << error << " " << errorString;
	    });

	QObject::connect(
	    m_cameraService.get(), &CameraStorageService::serviceTrackingFinished, this, [this]() {
		    m_recorder->stop();
	    });
}

void CameraStorage::setVideoSize(const size_t &videoSize)
{
	if (m_videoSize == videoSize) {
		return;
	}

	m_videoSize = videoSize;

	updateStorageCapacity();
}

void CameraStorage::setNumberOfVideo(const uint8_t &numberOfVideo)
{
	if (m_NumberOfVideo == numberOfVideo) {
		return;
	}

	m_NumberOfVideo = numberOfVideo;

	updateStorageCapacity();
}

void CameraStorage::setDurationForEach(const size_t &duration)
{
	if (m_duration == duration) {
		return;
	}

	m_duration = duration;

	updateStorageCapacity();
}

void CameraStorage::updateStorageCapacity()
{
}

void CameraStorage::attachToScreenCapture(QMediaCaptureSession *session)
{
	if (session) {
		m_screenCaptureSession = session;
		session->setRecorder(m_recorder.get());
		emit attachStatusOnCaptureSessionChanged(true);
	}
}

void CameraStorage::detachFromCurrent()
{
	m_recorder->stop();
	if (m_screenCaptureSession) {
		m_screenCaptureSession->setRecorder(nullptr);
	}
	emit attachStatusOnCaptureSessionChanged(false);
}

// The action to check the m_screenCaptureSession before invoking any operations
// should be replaced by the internal `ready state`

void CameraStorage::setRecordingPath(const QString &path)
{
	if (m_recordingPath == path) {
		return;
	}

	m_recordingPath = path;

	if (m_screenCaptureSession) {
		qWarning() << "Set path here " << path;
		m_recorder->setOutputLocation(QUrl::fromLocalFile(path));
	} else {
		qWarning() << "The recorder must be attached to Capture Session before using";
	}
}

bool CameraStorage::startRecording()
{
	bool res = false;
	if (m_screenCaptureSession) {
		qDebug() << "Request recording........................";
		if (m_recorder->isAvailable()) {
			res = true;
			m_cameraService->startTracking();
			qDebug() << "Service ready. Recoding.";
			m_recorder->setQuality(QMediaRecorder::HighQuality);
			m_recorder->record();
		} else {
			qWarning() << "The recording service is not ready to be used";
		}
	} else {
		qWarning() << "The recorder must be attached to Capture Session before using";
	}
	return res;
}

bool CameraStorage::stopRecording()
{
	bool res = false;
	if (m_screenCaptureSession) {
		res = true;
		qDebug() << "Start recording";
		m_recorder->stop();
		m_cameraService->stopTracking();
	} else {
		qWarning() << "The recorder must be attached to Capture Session before using";
	}
	return res;
}

void CameraStorage::stopImpl()
{
}
