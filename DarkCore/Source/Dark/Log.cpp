#include "dkpch.h"
#include "Log.h"
#include "spdlog/spdlog.h"

namespace Dark
{

	void Log::Trace(const char* string)
	{
		spdlog::trace(string);
	}

	void Log::Info(const char* string)
	{
		spdlog::info(string);
	}

	void Log::Warn(const char* string)
	{
		spdlog::warn(string);
	}

	void Log::Error(const char* string)
	{
		spdlog::error(string);
	}

	void Log::Critical(const char* string)
	{
		spdlog::critical(string);
	}

}
