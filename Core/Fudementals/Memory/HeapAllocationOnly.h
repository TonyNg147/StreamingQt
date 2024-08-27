#pragma once
#include <exception>
#include <iostream>

class HeapAllocationOnly
{
public:
	HeapAllocationOnly()
	{
		if (isOnStack()) {
			throw std::exception("Instance of this class must be allocated on Heap");
		}
	}

protected:
	bool isOnStack();
};
