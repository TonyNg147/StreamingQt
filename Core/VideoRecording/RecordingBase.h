#ifndef STORAGE_BASE_H
#define STORAGE_BASE_H
#include <QObject>
#include <QString>

class RecordingBase: public QObject 
{
    Q_OBJECT
    public:
    RecordingBase(QObject* parent = nullptr);
    virtual ~RecordingBase();
    virtual void setRecordingPath(const QString&);
    virtual bool startRecording() = 0;
    virtual bool stopRecording() = 0; 
    protected:
	virtual void stopImpl();
    virtual void startImpl();
    protected:
    QString m_recordingPath;
};
#endif 
