set(SOURCES DeleteLater.h executionhelper.h executionhelper.cpp
            singleapplication.h singleapplication.cpp)

add_library(Utils STATIC ${SOURCES})

target_link_libraries(Utils PUBLIC Qt6::Core Qt6::Gui Fudementals)

target_include_directories(Utils INTERFACE ./)
