#pragma once

#ifdef DK_DEBUG
	#define _CRTDBG_MAP_ALLOC
	#include <stdlib.h>
	#include <crtdbg.h>
#endif

#include <functional>
#include <memory>
#include <algorithm>
#include <array>
#include <string>
#include <unordered_map>
#include <vector>