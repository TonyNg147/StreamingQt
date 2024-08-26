import QtQuick
import HMI.Const

ButtonWithLayer{

    required property QtObject buttonRelatedAttr

	property list<State> stateManage: internal.predefinedStates

	scripts: QtObject{
		function toStateOFF() {
            manageInternalButtonState.state = "OFF"
        }
        
		function toStateON() {

            manageInternalButtonState.state = "ON"
        }
		function toStateACTIVE() {
            manageInternalButtonState.state = "ACTIVE"
        }
		function toStateINACTIVE() {
			// manageInternalButtonState.state = "ACTIVE"
		}
    }

	width: childrenRect.width
	height: childrenRect.height

    Rectangle{
        id: backgroundButton
        width: 60
        height: 60
        radius: 30
        Image{
            id: icon
            anchors.centerIn: parent
        }
    }

    Item{
        id: manageInternalButtonState
        states: stateManage
    }

    QtObject{
        id: internal

        property list<State> predefinedStates: [
            State{
                name: "ON"
                StateChangeScript{
                    script: {
						if (buttonRelatedAttr?.on?.source !== undefined ) {
							icon.source = buttonRelatedAttr.on.source
						}
						if (buttonRelatedAttr?.on?.color !== undefined ){ backgroundButton.color = buttonRelatedAttr.on.color}
                    }
                }
			},
            State{
                name: "INACTIVE"
                StateChangeScript{
                    script: {
                        if (buttonRelatedAttr?.inActive?.source !== undefined ) icon.source = buttonRelatedAttr.inActive.source
                        if (buttonRelatedAttr?.inActive?.color !== undefined ) backgroundButton.color = buttonRelatedAttr.inActive.color
                    }
                }
			},
            State{
                name: "ACTIVE"
                StateChangeScript{
                    script: {
						if (buttonRelatedAttr?.active?.source !== undefined ) icon.source = buttonRelatedAttr.active.source
						if (buttonRelatedAttr?.active?.color !== undefined ) backgroundButton.color = buttonRelatedAttr.active.color
                    }
                }
			},
			State{
				name: "OFF"
				StateChangeScript{
					script: {
						if (buttonRelatedAttr?.off?.source !== undefined ) icon.source = buttonRelatedAttr.off.source
						if (buttonRelatedAttr?.off?.color !== undefined ) backgroundButton.color = buttonRelatedAttr.off.color
					}
				}
			}
        ]
    }
}
