#include "camerastorageservice.h"
#include <QDebug>

CameraStorageServiceBase::CameraStorageServiceBase(QObject *parent)
    : QObject{parent}
{
}

CameraStorageService::CameraStorageService(int duration, int fileCount, const QString &fileName)
    : CameraStorageServiceBase{nullptr}
    , m_fileName{fileName}
    , m_duration{duration}
    , m_fileCount{fileCount}
{
	m_filePaths.reserve(fileCount);
	if (fileCount) {
		QString currentPath = m_fileName;
		for (size_t i = 0; i < m_fileCount; ++i) {
			m_filePaths.push_back(currentPath + "_" + QString::number(i) + ".mp4");
		}
	}
	m_trackingTimer.setInterval(m_duration);
	m_trackingTimer.setSingleShot(true);
	QObject::connect(
	    &m_trackingTimer, &QTimer::timeout, this, &CameraStorageService::onDueTimeArrived);
}

void CameraStorageService::setObservant(RecordingBase *observant)
{
	if (observant) {
		m_observant = observant;
	}
}

void CameraStorageService::startTracking()
{
	if (isValidService() && !m_isServiceRunning) {
		m_isServiceRunning = true;
		m_currentCount = 0;
		saveInNewFileIndex(m_currentCount);
		m_trackingTimer.start();
		emit serviceTrackingStarted();

	} else {
		qWarning() << "Not suppose to be run with the current setting";
	}
}

void CameraStorageService::stopTracking()
{
	if (m_isServiceRunning) {
		m_isServiceRunning = false;
		m_trackingTimer.stop();
		// Should we reset the currentCount at this point???
	}
}

void CameraStorageService::onDueTimeArrived()
{
	if (m_isServiceRunning) {
		if (++m_currentCount < m_fileCount) {
			saveInNewFileIndex(m_currentCount);
			m_trackingTimer.start();
		} else {
			m_isServiceRunning = false;
			emit serviceTrackingFinished();
		}
	}
}

bool CameraStorageService::isValidService()
{
	// Should valid the folder name of the given file
	return !m_fileName.isEmpty() && m_duration && m_fileCount && m_observant;
}

void CameraStorageService::saveInNewFileIndex(const int &index)
{
	if (m_observant) {
		m_observant->setRecordingPath(m_filePaths[index]);
	}
}
