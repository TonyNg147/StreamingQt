cmake_minimum_required(VERSION 3.16)

project(CustomVideoFrame VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 6.4 REQUIRED COMPONENTS Quick Multimedia Quick)

set(CMAKE_PREFIX_PATH ${CMAKE_SOURCE_DIR}/cmake)

find_package(PreCommit REQUIRED)

PreCommitInstallation()

qt_standard_project_setup()

add_subdirectory(Utils)
add_subdirectory(Core)
add_subdirectory(CustomVideoHandle)
add_subdirectory(assets)
add_subdirectory(HMI)
add_subdirectory(CameraHandle)
add_subdirectory(CameraStorage)

qt_add_executable(appCustomVideoFrame
    main.cpp
    CameraHandle/camerautils.h
    CameraHandle/camerautils.cpp

)

target_link_libraries(appCustomVideoFrame
    PRIVATE
    Qt6::Quick
    assets
    CustomVideoHandle
    HMI
    CameraHandle
    CameraStorage
)
