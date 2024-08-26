import QtQuick
import HMI.Const
MouseArea{
    id: buttonBase

    required property list<int> registerdStates

	required property int behavior

    property list<ButtonAttribute> attributeOfButtons

	property int buttonState: 1

    property QtObject scripts: scriptObject

    states: [
        State{
            name: "ON"
			when: internal.isEnteredState(0)
            StateChangeScript{
                script: {
					if (scripts.toStateON !== undefined) {
						scripts.toStateON()
                    }
                }
            }
        },
        State{
            name: "OFF"
            when: internal.isEnteredState(ComponentEnum.OFF)
            StateChangeScript{
				script: {
					if (scripts.toStateOFF !== undefined) {
						scripts.toStateOFF()
                    }
                }
            }
        },
        State{
            name: "INACTIVE"
            when: internal.isEnteredState(ComponentEnum.INACTIVE)
            StateChangeScript{
                script: {
					if (scripts.toStateINACTIVE !== undefined) {
						scripts.toStateINACTIVE()
                    }
                }
            }
        },
        State{
            name: "ACTIVE"
            when: internal.isEnteredState(ComponentEnum.ACTIVE)
            StateChangeScript{
				script: {
					if (scripts.toStateACTIVE !== undefined) {
						scripts.toStateACTIVE()
					}
                }
            }
		}
    ]

    Loader{
        id: inTimeLoadItemsLoader
        active: false
        sourceComponent: Repeater{
            model: internal.buttonAttrs
            delegate: Loader{
                id: buttonStateRepresent
                required property Component display
                required property int buttonState
                active: false
				states: State{
                    when: buttonStateRepresent.buttonState === buttonBase.buttonState
                    PropertyChanges{
                        target:buttonStateRepresent
                        active: true
                    }
                }
                sourceComponent: display
            }
        }
    }

    QtObject{
        id: internal
        property ListModel buttonAttrs: ListModel{}
		function isEnteredState(state) {
			let res = buttonBase.buttonState === state && registerdStates.indexOf(state) !== -1
			return res
        } 
    }

    QtObject{
        id: scriptObject
    }

    Component.onCompleted: {
		if (behavior === ComponentEnum.IntimeLoadItem) {
			if (attributeOfButtons.length === 0) {
                throw new Error("If you use the IntimeLoadItem, you must provide attributeOfButtons")
            }
            for (let attr of attributeOfButtons) {
                buttonAttrs.append({"display": attr.display, "buttonState": attr.buttonState})
            }

            inTimeLoadItemsLoader.active = true
        } else if (scripts.toStateON === undefined 
                 && scripts.toStateOFF === undefined
                 && scripts.toStateINACTIVE === undefined
                 && scripts.toStateACTIVE === undefined) {
                    throw new Error("If you choose to go with ScriptInvocation. You have to assign scripts with corresponding function");
        }
    }


}
