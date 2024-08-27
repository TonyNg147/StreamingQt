#ifndef CAMERA_STORAGE_SERVICE_H
#define CAMERA_STORAGE_SERVICE_H
#include <Memory/observerPtr.h>
#include <QObject>
#include <QTimer>
#include <RecordingBase.h>

class CameraStorageServiceBase : public QObject
{
	Q_OBJECT

public:
	CameraStorageServiceBase(QObject *parent = nullptr);
	virtual void setObservant(RecordingBase *observant) = 0;
	virtual void startTracking() = 0;
	virtual void stopTracking() = 0;
signals:
	void serviceTrackingFinished();
	void serviceTrackingStarted();

protected:
	observe_ptr<RecordingBase> m_observant = nullptr;
};

class CameraStorageService : public CameraStorageServiceBase
{
	Q_OBJECT

public:
	CameraStorageService(int duration, int fileCount, const QString &fileName);
	void setObservant(RecordingBase *observant) override;
	void startTracking() override;
	void stopTracking() override;

private:
	void onDueTimeArrived();
	bool isValidService();
	void saveInNewFileIndex(const int &);

private:
	QVector<QString> m_filePaths;
	QTimer m_trackingTimer;
	QString m_fileName;
	int m_duration = 0;
	int m_fileCount = 0;
	int m_currentCount = 0;
	bool m_isServiceRunning = false;
};

#endif // CAMERA_STORAGE_SERVICE_H
