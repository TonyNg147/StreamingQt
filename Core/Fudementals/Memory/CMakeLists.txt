
if(WIN32)
    set(SOURCES HeapAllocationOnly_win.cpp)
elseif(UNIX)
    set(SOURCES HeapAllocationOnly_unix.cpp)
endif()

if(NOT DEFINED SOURCES)
    message(FATAL_ERROR "Enironment not be supportted")
endif()


list(APPEND SOURCES
observerPtr.cpp
TrackableImpl.cpp
)

add_library(MemoryUtil STATIC ${SOURCES})

target_link_libraries(MemoryUtil PUBLIC SystemIF Qt6::Core)

