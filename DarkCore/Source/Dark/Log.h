#pragma once

namespace Dark
{

	class Log
	{
	public:
		void static Trace(const char* string);
		void static Info(const char* string);
		void static Warn(const char* string);
		void static Error(const char* string);
		void static Critical(const char* string);
	};

}
