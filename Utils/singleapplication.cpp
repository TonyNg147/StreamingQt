#include "singleapplication.h"
#include <QSharedMemory>

class SingleApplicationImpl
{
public:
	SingleApplicationImpl(const char *name)
	    : m_applicationName{name}
	{
		m_applicationSharedMem.setKey(name);
		if (m_applicationSharedMem.create(sizeof(void *))) {
			m_applicationSharedMem.attach();
		} else {
			qDebug() << "Only allow one application running each time";
			exit(0);
		}
	}

	~SingleApplicationImpl()
	{
		(void)m_applicationSharedMem.detach();
	}

private:
	QSharedMemory m_applicationSharedMem;
	const char *m_applicationName;
};

SingleApplication::SingleApplication(int argc, char **argv, const char *name)
    : QGuiApplication(argc, argv)
{
	m_impl.reset(new SingleApplicationImpl(name));
}

SingleApplication::~SingleApplication()
{
}
