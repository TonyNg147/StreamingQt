#include "HeapAllocationOnly.h"
#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

namespace {
struct StackLimit
{
	void *lowLimit;
	void *hightLimit;
};
} // namespace

bool HeapAllocationOnly::isOnStack()
{
	StackLimit stackLimit;
	size_t stackSize;

	pthread_attr_t atrr;
	if (pthread_attr_init(&atrr)) {
		fprintf(stderr, "Error when initializing stack attribute %s\n", strerror(errno));
		return false;
	}

	if (pthread_attr_getstack(&atrr, &stackLimit.lowLimit, &stackSize)) {
		fprintf(stderr, "Error when getting stack attribute %s\n", strerror(errno));
		return false;
	}

	(size_t &)stackLimit.hightLimit = stackSize + (size_t &)stackLimit.lowLimit;

	void *instanceAddress = static_cast<void *>(this);

	return lowLimit <= instanceAddress && instanceAddress <= hightLimit;
}
