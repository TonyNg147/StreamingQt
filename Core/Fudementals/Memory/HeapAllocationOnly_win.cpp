#include "HeapAllocationOnly.h"
// #include <Processthreadsapi.h>

#include <windows.h>

namespace {
struct StackLimit
{
	size_t lowLimit;
	size_t hightLimit;
};
} // namespace

bool HeapAllocationOnly::isOnStack()
{
	StackLimit stackLimit;
	GetCurrentThreadStackLimits(&stackLimit.lowLimit, &stackLimit.hightLimit);
	size_t addressToValue = (size_t)this;
	return stackLimit.lowLimit <= addressToValue && addressToValue <= stackLimit.hightLimit;
}
