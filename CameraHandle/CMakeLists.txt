qt_add_qml_module(CameraHandle STATIC
    URI CameraHandle
    VERSION 1.0
    NO_PLUGIN
    SOURCES
    cameraframeprocessor.cpp
    camerapool.cpp
    cameraTypeRegistration.h
    SOURCES camerascreencapture.h camerascreencapture.cpp
)

target_link_libraries(CameraHandle
    PUBLIC
    Qt6::Multimedia Qt6::Quick Core
    PRIVATE
    CorePrivate
)

target_include_directories(CameraHandle INTERFACE ./)
