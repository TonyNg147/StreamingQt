set(SOURCE SInterface.cpp SInterface.h BaseInterface.h IFManipulate.h
           IFRepresent.h)

add_library(SystemIF STATIC ${SOURCE})

target_include_directories(SystemIF INTERFACE ./)
