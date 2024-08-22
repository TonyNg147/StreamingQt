import QtQuick
import CustomVideoHandle
import assets
import CameraHandle
Window {
	width: 640
	height: 480
	visible: true
	title: qsTr("Hello World")

	// VideoSourcePool {
	// 	id: videoPool
	// 	source: "qrc:/assets/Night_dancer.mp4"
	// 	Component.onCompleted: {
	// 		videoPool.playVideo()
	// 	}
	// }

	// VideoFrameProcessor{
	// 	anchors.centerIn: parent
	// 	sourcePool: videoPool
	// 	width: 500
	// 	height: 500
	// }
	CameraPool{
		id: cameraPool
		position: CameraUtil.FRONT
		Component.onCompleted: {
			cameraPool.startStreaming()
		}
	}
	CameraFrameProcessor{
		anchors.centerIn: parent
		sourcePool: cameraPool
		width: 500
		height: 500
	}
}
