#pragma once
#include "Log.h"

namespace Dark
{

	class Logger
	{
	public:
		static void trace() {};

		template<typename String, typename ... Strings>
		static void trace(String var1, const Strings&... var2)
		{
			Log::Trace(var1);

			trace(var2...);
		}

		static void info() {};

		template<typename String, typename ... Strings>
		static void info(String var1, const Strings&... var2)
		{
			Log::Info(var1);

			info(var2...);
		};

		static void warn() {};

		template<typename String, typename ... Strings>
		static void warn(String var1, const Strings&... var2)
		{
			Log::Warn(var1);

			warn(var2...);
		};

		static void error() {};

		template<typename String, typename ... Strings>
		static void error(String var1, const Strings&... var2)
		{
			Log::Error(var1);

			error(var2...);
		};

		static void critical() {};

		template<typename String, typename ... Strings>
		static void critical(String var1, const Strings&... var2)
		{
			Log::Critical(var1);

			critical(var2...);
		};
	};

}