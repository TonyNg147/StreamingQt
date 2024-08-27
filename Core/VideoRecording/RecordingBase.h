#ifndef STORAGE_BASE_H
#define STORAGE_BASE_H
#include <Memory/TrackableImpl.h>
#include <QObject>
#include <QString>
#include <SystemIF/IFManipulate.h>

class RecordingBase
    : public QObject
    , public TrackableImpl
{
	Q_OBJECT

public:
	RecordingBase(QObject *parent = nullptr);
	virtual ~RecordingBase();
	virtual void setRecordingPath(const QString &);
	virtual bool startRecording() = 0;
	virtual bool stopRecording() = 0;

protected:
	virtual void stopImpl();
	virtual void startImpl();

protected:
	QString m_recordingPath;
};

REGISTER_IF(RecordingBase)
#endif
