#include "executionhelper.h"
#include <QThreadPool>
#include <QRunnable>
#include <QDebug>

class ExecuteOrRetry: public QRunnable
{
public:
	ExecuteOrRetry(std::function<void()>&& task, std::function<bool()>&& condition, int count)
		:m_task{std::move(task)}
		,m_condition{std::move(condition)}
	{
		Q_ASSERT_X(m_condition && m_task, "The validity", "Task and condition must be assigned");
		setAutoDelete(false);
		if (count > 1) {
			m_count = count;
		}
	}

	~ExecuteOrRetry() {}

	//If the condition is met, we execute normally. Otherwise, sleep 1 second and re-check the condition
	//the loop will last m_count times
	void run() override{
		if (m_condition()) {
			m_task();
			delete this;
		} else {
			if (m_count) {
				--m_count;
				QThread::sleep(1);
				QThreadPool::globalInstance()->tryStart(this);
			}
		}
	}
private:
	std::function<void()> m_task;
	std::function<bool()> m_condition;
	int m_count = 0;
};

void ExecutionHelper::execOnlyCondMetOrRetry(std::function<void()>&& task, std::function<bool()>&& condition, int count)
{
	ExecuteOrRetry *taskOrRetry = new ExecuteOrRetry(std::move(task), std::move(condition), count);
	QThreadPool::globalInstance()->start(taskOrRetry);
}
