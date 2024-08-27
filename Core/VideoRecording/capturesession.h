#pragma once
#include <Memory/TrackableImpl.h>
#include <SystemIF/IFManipulate.h>
class QMediaCaptureSession;

class CMediaCaptureSession : public TrackableImpl
{
public:
	virtual ~CMediaCaptureSession();
	virtual QMediaCaptureSession *get() = 0;
};

REGISTER_IF(CMediaCaptureSession)
