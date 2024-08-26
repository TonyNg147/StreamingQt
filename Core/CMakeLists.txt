
set(
    SOURCES
    FrameProcessing/FrameSourceBase.h
    VideoRecording/RecordingBase.h
    VideoRecording/RecordingBase.cpp
    VideoRecording/VideoRecordingBase.cpp
    VideoRecording/VideoRecordingBase.h

)

set(
    SOURCE_PRIVATE
    FrameProcessing/p/FrameSourceBaseImpl.h
)

add_library(Core STATIC ${SOURCES})

add_library(CorePrivate STATIC ${SOURCE_PRIVATE})

target_link_libraries(Core PUBLIC Qt6::Multimedia Qt6::Quick Utils)
target_link_libraries(CorePrivate PUBLIC Qt6::Multimedia Qt6::Quick Utils)

target_include_directories(Core
INTERFACE ./FrameProcessing
./VideoRecording
)
target_include_directories(CorePrivate INTERFACE ./FrameProcessing/p)
