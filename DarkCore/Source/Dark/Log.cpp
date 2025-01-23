#include "dkpch.h"
#include "Log.h"
#include "spdlog/spdlog.h"

namespace Dark
{

#define CreateLoggerFunctions(Name, name) void Log::##Name(const char* string) { spdlog::##name(string); }\
										  void Log::##Name(int integer) { spdlog::##name(integer); }\
										  void Log::##Name(bool boolean) { spdlog::##name(boolean); }\
										  void Log::##Name(float floating) { spdlog::##name(floating); }\
										  void Log::##Name(double doubling) { spdlog::##name(doubling); }
									
	CreateLoggerFunctions(Trace, trace);
	CreateLoggerFunctions(Info, info);
	CreateLoggerFunctions(Warn, warn);
	CreateLoggerFunctions(Error, error);
	CreateLoggerFunctions(Critical, critical);

	//void Log::Info(const char* string)
	//{
	//	spdlog::info(string);
	//}

	//void Log::Warn(const char* string)
	//{
	//	spdlog::warn(string);
	//}

	//void Log::Error(const char* string)
	//{
	//	spdlog::error(string);
	//}

	//void Log::Critical(const char* string)
	//{
	//	spdlog::critical(string);
	//}

}
