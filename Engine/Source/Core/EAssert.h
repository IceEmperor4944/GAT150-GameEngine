#pragma once
#include <string>

#ifdef _DEBUG
	#define ASSERT(expr) ((expr) ? (void)0 : CustomAssert(#expr, __FILE__, __LINE__))
#else
	#define ASSERT(expr) (void)0
#endif

void CustomAssert(const std::string& expression, const std::string& filename, int line);