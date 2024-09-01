#ifndef CAMERAFRAMEPROCESSOR_H
#define CAMERAFRAMEPROCESSOR_H

#include <RoundedImage.h>

#include "camerapool.h"
#include "screencapture.h"

class CameraFrameProcessor : public RoundedImage
{
	Q_OBJECT
	Q_PROPERTY(CameraPool *sourcePool READ sourcePool WRITE setSourcePool NOTIFY sourcePoolChanged)

public:
	explicit CameraFrameProcessor(QObject *parent = nullptr);

	CameraPool *sourcePool() const;
	void setSourcePool(CameraPool *newSourcePool);

public slots:
	void capture();

private:
	void onVideoFrameChanged(const QImage &);

signals:
	void sourcePoolChanged();

private:
	CameraPool *m_sourcePool = nullptr;
	std::unique_ptr<ScreenCapture> m_screenCapture;
};

#endif // CAMERAFRAMEPROCESSOR_H
