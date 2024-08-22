#include "videosourcepool.h"
#include <QVideoSink>
#include <QMediaPlayer>
#include <QVideoFrame>
#include <QAudioOutput>

class VideoSourcePoolImpl: public QObject {
	Q_OBJECT
public:
	VideoSourcePoolImpl(QObject* parent = nullptr);

	void setVideoSource(const QString&);

	QString getSource() const;

	void play();
signals:
	void imageFrameChanged(const QImage&);

private:
	void onVideoFrameChanged(const QVideoFrame&);
private:
	QMediaPlayer m_player;
	QVideoSink m_videoSink;
	std::optional<QString> m_videoSource;


};

VideoSourcePoolImpl::VideoSourcePoolImpl(QObject* parent)
	:QObject{parent}
{
	QAudioOutput* output = new QAudioOutput(&m_player);
	output->setVolume(50);
	m_player.setAudioOutput(output);
	m_player.setVideoSink(&m_videoSink);
	QObject::connect(&m_videoSink,&QVideoSink::videoFrameChanged, this, &VideoSourcePoolImpl::onVideoFrameChanged);
}

void VideoSourcePoolImpl::onVideoFrameChanged(const QVideoFrame& videoFrame)
{

	// maybe we can make a cache at this point to improve the performance
	QImage videoFrameToImage = videoFrame.toImage();
	emit imageFrameChanged(videoFrameToImage);
}

void VideoSourcePoolImpl::setVideoSource(const QString& videoFrame) {
	if (m_videoSource == videoFrame) {
		return;
	}

	if (m_player.isPlaying()) {
		m_player.stop();
	}

	m_videoSource = videoFrame;
	m_player.setSource(m_videoSource.value());
}

QString VideoSourcePoolImpl::getSource() const {
	return m_videoSource.value_or(QString{});
}

void VideoSourcePoolImpl::play() {
	Q_ASSERT_X(m_videoSource.has_value(), "Play Video", "The video path must be set before playing");

	if (m_player.isPlaying()) return;
	m_player.play();

}


VideoSourcePool::VideoSourcePool()
	:m_impl{new VideoSourcePoolImpl()}
{
	m_impl->moveToThread(&m_processingVideoThread);
	QObject::connect(m_impl.get(), &VideoSourcePoolImpl::imageFrameChanged, this, &VideoSourcePool::imageFrameChanged, Qt::QueuedConnection);
	m_processingVideoThread.start();
}

VideoSourcePool::~VideoSourcePool()
{
	m_processingVideoThread.quit();
	m_processingVideoThread.wait();
}

QString VideoSourcePool::source() const
{
	return m_source;
}

void VideoSourcePool::setSource(const QString &newSource)
{
	if (m_source == newSource)
		return;
	m_source = newSource;
	m_impl->setVideoSource(newSource);
	emit sourceChanged();
}

void VideoSourcePool::playVideo()
{
	m_impl->play();
}

#include <videosourcepool.moc>

