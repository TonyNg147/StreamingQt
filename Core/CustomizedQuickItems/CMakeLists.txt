set(SOURCES
AnimatedPaintedItem.h
AnimatedPaintedItem.cpp
RoundedImage.h
RoundedImage.cpp
AnchorsItem.cpp
AnchorsItem.h
)

add_library(CustomizedQuickItems STATIC ${SOURCES}
    painteditem.h painteditem.cpp)

target_link_libraries(CustomizedQuickItems 
    PUBLIC
    Qt6::Core
    Qt6::Quick
)

target_include_directories(CustomizedQuickItems
    PUBLIC
        ./
)
