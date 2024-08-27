#pragma once

#include "IFRepresent.h"
#include <type_traits>

template<typename T>
struct ValidInterface : public std::false_type
{
};

#define REGISTER_IF(TYPE)                                                                          \
	template<>                                                                                     \
	struct ValidInterface<TYPE> : public std::true_type                                            \
	{                                                                                              \
		inline static const char *name = #TYPE;                                                    \
	};

template<typename IF>
IFRepresent id()
{
	static_assert(
	    ValidInterface<IF>::value,
	    "The class must be an interface and be declared with REGISTER_IF");
	return IFRepresent(ValidInterface<IF>::name);
};
