#pragma once
#include "spdlog/spdlog.h"

#define DK_CORE_TRACE(...) spdlog::trace(__VA_ARGS__);
#define DK_CORE_INFO(...) spdlog::info(__VA_ARGS__);
#define DK_CORE_WARN(...) spdlog::warn(__VA_ARGS__);
#define DK_CORE_ERROR(...) spdlog::error(__VA_ARGS__);
#define DK_CORE_CRITICAL(...) spdlog::critical(__VA_ARGS__);

#define DK_TRACE(...) spdlog::trace(__VA_ARGS__);
#define DK_INFO(...) spdlog::info(__VA_ARGS__);
#define DK_WARN(...) spdlog::warn(__VA_ARGS__);
#define DK_ERROR(...) spdlog::error(__VA_ARGS__);
#define DK_CRITICAL(...) spdlog::critical(_VA__ARGS__);