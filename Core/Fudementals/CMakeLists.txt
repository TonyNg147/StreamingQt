add_subdirectory(SystemIF)
add_subdirectory(Memory)

add_library(Fudementals INTERFACE)

target_link_libraries(Fudementals INTERFACE MemoryUtil SystemIF)

target_include_directories(Fudementals INTERFACE ./)

