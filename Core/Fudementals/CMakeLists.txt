add_subdirectory(Memory)

add_library(Fudementals INTERFACE)

target_link_libraries(Fudementals INTERFACE HeapAllocation)
