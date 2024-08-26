#include "RecordingBase.h"

RecordingBase::RecordingBase(QObject *parent)
    : QObject{parent}
    , m_recordingPath{QString{"Undefined"}}
{
}

RecordingBase::~RecordingBase()
{
	stopImpl();
}

void RecordingBase::setRecordingPath(const QString &path)
{
	m_recordingPath = path;
}

void RecordingBase::stopImpl()
{
}

void RecordingBase::startImpl()
{
}
