#ifndef SINGLEAPPLICATION_H
#define SINGLEAPPLICATION_H

#include <memory>
#include <QGuiApplication>

class SingleApplicationImpl;

class SingleApplication : public QGuiApplication
{
	Q_OBJECT

public:
	SingleApplication(int, char **, const char *);
	~SingleApplication();

private:
	std::unique_ptr<SingleApplicationImpl> m_impl;
};

#endif // SINGLEAPPLICATION_H
