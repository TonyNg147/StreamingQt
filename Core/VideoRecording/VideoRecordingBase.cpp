#include "VideoRecordingBase.h"

VideoRecordingBase::VideoRecordingBase(QObject *parent)
    : RecordingBase{parent}
    , m_screenCaptureSession{nullptr}
{
}

VideoRecordingBase::~VideoRecordingBase()
{
}
