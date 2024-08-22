qt_add_qml_module(CustomVideoHandle STATIC
    URI CustomVideoHandle
    VERSION 1.0
    NO_PLUGIN
    SOURCES
    videosourcepool.cpp
    videoframeprocessor.cpp
    videoTypeRegistration.h
)

target_link_libraries(CustomVideoHandle PUBLIC Qt6::Multimedia Qt6::Quick)

target_include_directories(CustomVideoHandle INTERFACE ./)
