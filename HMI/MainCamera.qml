import QtQuick
import QtQuick.Layouts
import CustomVideoHandle
import assets
import CameraHandle
import QtQuick.Controls
import CameraStorage
import HMI.Components
import HMI.Const
Window {
	id: root
	width: 1300
	height: 700
	color: "transparent"
	visible: true
	title: qsTr("Hello World")
	// flags: Qt.FramelessWindowHint

	Rectangle{
		anchors.fill: parent
		color: "#161929"
		radius: 29
	}

	Item{
		anchors.bottom: parent.bottom
		width: 1306
		height: 140
		RowLayout
		{
			anchors.centerIn: parent
			spacing: 20
			Repeater{
				model: videoButton.props
				delegate:
					VideoSettingButton{
					required property QtObject processor
					buttonState: buttonState
					onClicked: {
						processor.processClicked(this);
					}
				}
			}
		}
	}

	VideoButtonProsDefault{
		id:videoButton
		handler: QtObject{
			function screenCaptureOn() {
				internal.cameraFrameProcessor.capture()
			}
		}
	}

	QtObject{
		id: internal
		property CameraFrameProcessor cameraFrameProcessor
	}

	Loader{
		id: cameraLoader
		y: 168 - 140
		x: 30
		width: 1246
		height: 558
		active: false
		sourceComponent: Component {
			Item{
				// CameraStorageInstance{
				// 	id: cameraStorage
				// 	Component.onCompleted: {
				// 		cameraStorage.attachToScreenCapture(cameraPool.captureSession)
				// 	}
				// 	onAttachStatusOnCaptureSessionChanged: function(status) {
				// 		if (status) {
				// 			cameraStorage.startRecording()
				// 		}
				// 	}
				// }

				CameraPool{
					id: cameraPool
					position: CameraUtil.FRONT
					Component.onCompleted: {
						cameraPool.start()
					}
				}

				CameraFrameProcessor{
					id: cameraFrameProcessor
					anchors.centerIn: parent
					sourcePool: cameraPool
					width: 1246
					height: 558
					Component.onCompleted: {
						internal.cameraFrameProcessor = cameraFrameProcessor
					}
				}
			}
		}
	}

}
