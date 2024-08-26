pragma Singleton
import QtQuick

QtObject{
	enum ButtonState{
		ON,
		OFF,
		INACTIVE,
		ACTIVE
	}

    enum ButtonStateChangeBehavior {
        // For the item corresponding with the state that ain't avaiable at the initial
        // until its state reached
        IntimeLoadItem,
        // All the item are there but some restrictions are applied: visibility, order, and so on.
		ScriptInvocation
	}

}
