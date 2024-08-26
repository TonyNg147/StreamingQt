#ifndef CAMERASTORAGE_H
#define CAMERASTORAGE_H
#include <cstdint>
class VideoStorageBase
{
	public:
		virtual void setVideoSize(const size_t&) = 0;
		virtual void setNumberOfVideo(const uint8_t&) = 0;
		virtual void setDurationForEach(const size_t&) = 0;

	protected:
		virtual void updateStorageCapacity() = 0;
	protected:
		size_t m_videoSize = {0};
		size_t m_NumberOfVideo = {0};
		size_t m_duration = {0};
};

#endif // CAMERASTORAGE_H
