set(SOURCES
screencapture.h screencapture.cpp
camerascreencapture.h camerascreencapture.cpp
)

add_library(CameraCaptureService STATIC ${SOURCES})

target_link_libraries(CameraCaptureService
    PUBLIC
    Qt6::Quick
    Core
)

target_include_directories(CameraCaptureService INTERFACE ./)
