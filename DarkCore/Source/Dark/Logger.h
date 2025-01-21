#pragma once
#include "spdlog/spdlog.h"

namespace Dark
{

	class Logger
	{
	public:
		template<typename String, typename ... Strings>
		static void trace(String var1, const Strings&... var2)
		{
			spdlog::trace(var1);
		}

		template<typename String, typename ... Strings>
		static void info(String var1, const Strings&... var2)
		{
			spdlog::info(var1);
		}

		template<typename String, typename ... Strings>
		static void warn(String var1, const Strings&... var2)
		{
			spdlog::warn(var1);
		};

		template<typename String, typename ... Strings>
		static void error(String var1, const Strings&... var2)
		{
			spdlog::error(var1);
		};

		template<typename String, typename ... Strings>
		static void critical(String var1, const Strings&... var2)
		{
			spdlog::critical(var1);
		};
	};

}