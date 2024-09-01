add_subdirectory(Const)
add_subdirectory(Assets)
add_subdirectory(Components)

qt_add_qml_module(HMI STATIC
    URI HMI
    NO_PLUGIN
    VERSION 1.0
    QML_FILES Main.qml MainCamera.qml
)

target_link_libraries(HMI
    PUBLIC
    HMIAssets
    HMIComponents
    HMIConst
)
