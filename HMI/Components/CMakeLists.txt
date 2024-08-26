set(QML_FILE_CUSTOM
Fudamentals/AbstractButtonWithState.qml
Fudamentals/ButtonWithLayer.qml
Fudamentals/VideoSettingButton.qml
VideoButtonProsDefault.qml
)

qt_add_qml_module(HMIComponents STATIC
    URI HMI.Components
    NO_PLUGIN
    VERSION 1.0
    QML_FILES
        ${QML_FILE_CUSTOM}
)

target_link_libraries(HMIComponents PRIVATE HMIConst)
