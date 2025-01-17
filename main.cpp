#include <cameraStorageTypeRegistration.h>
#include <cameraTypeRegistration.h>
#include <camerautils.h>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <singleapplication.h>
#include <videoTypeRegistration.h>

int main(int argc, char *argv[])
{
	SingleApplication app(argc, argv, "CameraStreamingApp");

	QQmlApplicationEngine engine;
	CustomVideo::registerType();
	CameraHandle::registerType();
	CameraStorageNs::registerType();

	qDebug() << "Camera avaiable " << CameraUtil::cameraAvailable();

	const QUrl url(QStringLiteral("qrc:/HMI/MainCamera.qml"));

	QObject::connect(
	    &engine,
	    &QQmlApplicationEngine::objectCreationFailed,
	    &app,
	    []() { QCoreApplication::exit(-1); },
	    Qt::QueuedConnection);
	engine.load(url);

	return app.exec();
}
