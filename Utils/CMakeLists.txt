
set(SOURCES
DeleteLater.h
executionhelper.h executionhelper.cpp
)

add_library(Utils STATIC ${SOURCES}
)

target_link_libraries(Utils
    PUBLIC
        Qt6::Core
	Fudementals
)

target_include_directories(Utils INTERFACE ./)
