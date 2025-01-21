#pragma once
#include "spdlog/spdlog.h"

namespace Dark
{

	class Logger
	{
	public:
		static void trace() {};

		template<typename String, typename ... Strings>
		static void trace(String var1, const Strings&... var2)
		{
			spdlog::trace(var1);

			critical(var2...);
		}

		static void info() {};

		template<typename String, typename ... Strings>
		static void info(String var1, const Strings&... var2)
		{
			spdlog::info(var1);

			info(var2...);
		}

		static void warn() {};

		template<typename String, typename ... Strings>
		static void warn(String var1, const Strings&... var2)
		{
			spdlog::warn(var1);

			warn(var2...);
		};

		static void error() {};

		template<typename String, typename ... Strings>
		static void error(String var1, const Strings&... var2)
		{
			spdlog::error(var1);

			error(var2...);
		};

		static void critical() {};

		template<typename String, typename ... Strings>
		static void critical(String var1, const Strings&... var2)
		{
			spdlog::critical(var1);

			critical(var2...);
		};
	};

}