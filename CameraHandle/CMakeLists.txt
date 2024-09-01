qt_add_qml_module(
  CameraHandle
  STATIC
  URI
  CameraHandle
  VERSION
  1.0
  NO_PLUGIN
  SOURCES
  cameraframeprocessor.cpp
  camerapool.cpp
  cameraTypeRegistration.h)

add_subdirectory(CameraCaptureService)
add_subdirectory(Helpers)

target_link_libraries(
  CameraHandle
  PUBLIC Qt6::Multimedia Qt6::Quick Core CameraCaptureService CameraHelpers
  PRIVATE CorePrivate)

target_include_directories(CameraHandle INTERFACE ./)
