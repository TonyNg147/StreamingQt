#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <videoTypeRegistration.h>
int main(int argc, char *argv[])
{
	QGuiApplication app(argc, argv);

	QQmlApplicationEngine engine;
	CustomVideo::registerType();
	const QUrl url(QStringLiteral("qrc:/HMI/Main.qml"));
	QObject::connect(
		&engine,
		&QQmlApplicationEngine::objectCreationFailed,
		&app,
		[]() { QCoreApplication::exit(-1); },
		Qt::QueuedConnection);
	engine.load(url);

	return app.exec();
}
