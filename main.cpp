#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <videoTypeRegistration.h>
#include <cameraTypeRegistration.h>
#include <cameraStorageTypeRegistration.h>
#include <camerautils.h>
int main(int argc, char *argv[])
{
	QGuiApplication app(argc, argv);

	QQmlApplicationEngine engine;
	CustomVideo::registerType();
	CameraHandle::registerType();
	CameraStorageNs::registerType();

	qDebug() << "Camera avaiable " << CameraUtil::cameraAvailable();

	const QUrl url(QStringLiteral("qrc:/HMI/MainCamera.qml"));

	// QThread::sleep(10);
	QObject::connect(
		&engine,
		&QQmlApplicationEngine::objectCreationFailed,
		&app,
		[]() { QCoreApplication::exit(-1); },
		Qt::QueuedConnection);
		engine.load(url);



	return app.exec();
}
