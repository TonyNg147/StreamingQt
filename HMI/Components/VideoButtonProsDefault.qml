import QtQuick
import QtQuick.Layouts
import CustomVideoHandle
import assets
import CameraHandle
import QtQuick.Controls
import CameraStorage
import HMI.Components
import HMI.Const

QtObject{
	id: videoButtonDefaultProps
	property QtObject handler
	property list<QtObject> props: [
		QtObject{
			property list<int> registerdStates: [ComponentEnum.ON, ComponentEnum.OFF]
			property int buttonState: ComponentEnum.OFF
			property QtObject buttonRelatedAttr: QtObject{
				property QtObject on: QtObject{
					property string source: "qrc:/HMI/Assets/Icon/VideoIconOn.png"
					property color color: "#1A71FF"
				}
				property QtObject off: QtObject{
					property string source: "qrc:/HMI/Assets/Icon/VideoIconOff.png"
					property color color: "#1E2757"
				}
			}
			property QtObject processor: QtObject{
				function processClicked(target){
					let newState;
					if (target.buttonState === ComponentEnum.ON) {
						newState = ComponentEnum.OFF
						cameraLoader.active = false
					} else if (target.buttonState === ComponentEnum.OFF) {
						newState = ComponentEnum.ON
						cameraLoader.active = true
					} else {

					}
					target.buttonState = newState;
				}
			}
		},
		QtObject{
			property list<int> registerdStates: [ComponentEnum.OFF, ComponentEnum.ACTIVE]
			property int buttonState: ComponentEnum.OFF
			property QtObject buttonRelatedAttr: QtObject{
				property QtObject off: QtObject{
					property string source: "qrc:/HMI/Assets/Icon/RecordIconOff.png"
					property color color: "#1E2757"
				}
				property QtObject active: QtObject{
					property string source: "qrc:/HMI/Assets/Icon/RecordIconActive.png"
					property color color: "red"
				}
			}
			property QtObject processor: QtObject{
				function processClicked(target){
					let newState;
					if (target.buttonState === ComponentEnum.OFF) {

						newState = ComponentEnum.ACTIVE
					} else if (target.buttonState === ComponentEnum.ACTIVE) {
						newState = ComponentEnum.OFF
					} else {

					}
					target.buttonState = newState;
				}
			}
		},
		QtObject{
			property list<int> registerdStates: [ComponentEnum.OFF, ComponentEnum.ON]
			property int buttonState: ComponentEnum.OFF
			property QtObject buttonRelatedAttr: QtObject{
				property QtObject off: QtObject{
					property string source: "qrc:/HMI/Assets/Icon/ScreenCaptureOff.svg"
					property color color: "#1E2757"
				}
				property QtObject on: QtObject{
					property string source: "qrc:/HMI/Assets/Icon/ScreenCaptureOn.svg"
					property color color: "#1A71FF"
				}
			}
			property QtObject processor: QtObject{
				function processClicked(target){
					let newState;
					if (target.buttonState === ComponentEnum.ON) {
						newState = ComponentEnum.OFF
						// cameraFrameProcessor.capture = false
					} else if (target.buttonState === ComponentEnum.OFF) {
						newState = ComponentEnum.ON
						if (handler?.screenCaptureOn) {
							handler.screenCaptureOn()
						}
					} else {

					}
					target.buttonState = newState;
				}
			}
		}
	]
}
