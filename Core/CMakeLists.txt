
set(
    SOURCES
    FrameProcessing/FrameSourceBase.h
    VideoRecording/RecordingBase.h
    VideoRecording/RecordingBase.cpp
    VideoRecording/VideoRecordingBase.cpp
    VideoRecording/VideoRecordingBase.h
    VideoRecording/capturesession.cpp
    VideoRecording/capturesession.h

)

set(
    SOURCE_PRIVATE
    FrameProcessing/p/FrameSourceBaseImpl.h
)

add_subdirectory(Fudementals)
add_subdirectory(CustomizedQuickItems)

add_library(Core STATIC ${SOURCES}
    VideoRecording/capturesession.h VideoRecording/capturesession.cpp)


add_library(CorePrivate STATIC ${SOURCE_PRIVATE})

target_link_libraries(Core PUBLIC Qt6::Multimedia Qt6::Quick Utils Fudementals CustomizedQuickItems)
target_link_libraries(CorePrivate PUBLIC Qt6::Multimedia Qt6::Quick Utils Fudementals CustomizedQuickItems)

target_include_directories(Core
INTERFACE ./FrameProcessing
./VideoRecording
)
target_include_directories(CorePrivate INTERFACE ./FrameProcessing/p)
