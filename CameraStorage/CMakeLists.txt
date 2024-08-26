
set(SOURCES
camerastorage.h
camerastorage.cpp
camerastorageservice.cpp
camerastorageservice.h
cameraStorageTypeRegistration.h
)

add_library(CameraStorage STATIC ${SOURCES})

target_link_libraries(CameraStorage PUBLIC Qt6::Multimedia Qt6::Quick)

target_include_directories(CameraStorage INTERFACE ./)

target_link_libraries(CameraStorage
    PUBLIC
    CameraHandle
    Core
)
