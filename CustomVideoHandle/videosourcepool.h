#ifndef VIDEOSOURCEPOOL_H
#define VIDEOSOURCEPOOL_H

#include <QObject>

#include <QScopedPointer>
#include <QThread>

class VideoSourcePoolImpl;

class VideoSourcePool: public QObject
{
	Q_OBJECT
	Q_PROPERTY(QString source READ source WRITE setSource NOTIFY sourceChanged)
public:
	VideoSourcePool();
	~VideoSourcePool();
	QString source() const;
	void setSource(const QString &newSource);

public slots:
	void playVideo();
signals:
	void sourceChanged();
	void imageFrameChanged(const QImage&);

private:
	QThread m_processingVideoThread;
	QString m_source;
	QScopedPointer<VideoSourcePoolImpl, QScopedPointerDeleteLater> m_impl;
};

#endif // VIDEOSOURCEPOOL_H
