set(SOURCES
animationhelper.h animationhelper.cpp
screencapturehelper.h screencapturehelper.cpp
)

add_library(CameraHelpers STATIC ${SOURCES})

target_link_libraries(CameraHelpers
    PUBLIC
    Qt6::Quick
    Core
    CameraCaptureService
)

target_include_directories(CameraHelpers INTERFACE ./)
