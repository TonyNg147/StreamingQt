#include "camerastorageservice.h"
#include <QDebug>


CameraStorageServiceBase::CameraStorageServiceBase(QObject *parent)
	:QObject{parent}
{

}


CameraStorageService::CameraStorageService(int duration, int fileCount, const QString &fileName)
	:CameraStorageServiceBase{nullptr}
	,m_fileName{fileName}
	,m_duration{duration}
	,m_fileCount{fileCount}
{
	m_filePaths.reserve(fileCount);
	qWarning() << "Get file count " << m_fileCount << " " << m_filePaths.size();
	if (fileCount) {
		QString currentPath = m_fileName;
		for (size_t i = 0; i < m_fileCount; ++i) {
			m_filePaths.push_back(currentPath + "_" + QString::number(i) + ".mp4");
		}
	}
	qWarning() << "Call at this place " << m_duration;
	m_trackingTimer.setInterval(m_duration);
	m_trackingTimer.setSingleShot(true);
	QObject::connect(&m_trackingTimer, &QTimer::timeout, this, &CameraStorageService::onDueTimeArrived);
}

void CameraStorageService::setObservant(RecordingBase *observant)
{
	if (observant) {
		m_observant = observant;
	}
}

void CameraStorageService::startTracking()
{
	qWarning() << "Is valid service " << isValidService() << " " << m_isServiceRunning;
	if (isValidService() && !m_isServiceRunning) {
		qWarning() << __LINE__;
		m_isServiceRunning = true;
		qWarning() << __LINE__;
		m_currentCount = 0;
		qWarning() << __LINE__;
		saveInNewFileIndex(m_currentCount);
		qWarning() << __LINE__;
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
	m_observant->setRecordingPath(m_filePaths[index]);

}

