#ifndef EXECUTIONHELPER_H
#define EXECUTIONHELPER_H
#include <functional>
class ExecutionHelper
{
public:
	ExecutionHelper() = default;

	void execOnlyCondMetOrRetry(std::function<void()>&& task, std::function<bool()>&& condition, int count = 1);
};

#endif // EXECUTIONHELPER_H
