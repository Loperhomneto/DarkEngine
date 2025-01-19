#pragma once

#include "Logger.h"

#ifdef DK_DEBUG
#define DK_ENABLE_ASSERTS
#endif

#ifdef DK_ENABLE_ASSERTS
#define DK_ASSERT(x, ...) { if(!(x)) { DK_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define DK_CORE_ASSERT(x, ...) { if(!(x)) { DK_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
#define DK_ASSERT(x, ...)
#define DK_CORE_ASSERT(x, ...)
#endif