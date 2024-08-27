set(SOURCE)

if(WIN32)
    set(SOURCE HeapAllocationOnly_win.cpp)
elseif(UNIX)
    set(SOURCE HeapAllocationOnly_unix.cpp)
endif()

if(NOT DEFINED SOURCE)
    message(FATAL_ERROR "Enironment not be supportted")
endif()

add_library(HeapAllocation STATIC ${SOURCE})

target_link_libraries(HeapAllocation PUBLIC Qt6::Core)

target_include_directories(HeapAllocation INTERFACE ./)
