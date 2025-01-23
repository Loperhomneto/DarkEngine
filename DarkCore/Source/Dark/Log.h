#pragma once

namespace Dark
{

#define CreateLoggerHeaders(Name) void static Name(const char* string);\
								  void static Name(int integer);\
								  void static Name(float floating);\
								  void static Name(double doubling);\
								  void static Name(bool boolean);
	class Log
	{
	public:
		//void static Trace(const char* string);
		//void static Info(const char* string);
		//void static Warn(const char* string);
		//void static Error(const char* string);
		//void static Critical(const char* string);
		CreateLoggerHeaders(Trace)
		CreateLoggerHeaders(Info)
		CreateLoggerHeaders(Warn)
		CreateLoggerHeaders(Error)
		CreateLoggerHeaders(Critical)
	};

}
