#pragma once

#include <memory>

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Bezel {

	/*
		Denne log klassen er laget for å ta i bruk loggins biblioteket spdlog.h
	*/
	class BEZEL_API Log {
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	public:
		static void Init();
		//static spdlog::logger* GetCoreLogger();
		//static spdlog::logger* GetClientLogger();


		static std::shared_ptr<spdlog::logger> GetCoreLogger();
		static std::shared_ptr<spdlog::logger> GetClientLogger();


	};
}

/*
	MACRO DEFINITIONS CORE
*/
#define BZ_CORE_ERROR(...)		::Bezel::Log::GetCoreLogger()->error(__VA_ARGS__)
#define BZ_CORE_TRACE(...)		::Bezel::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define BZ_CORE_FATAL(...)		::Bezel::Log::GetCoreLogger()->fatal(__VA_ARGS__)
#define BZ_CORE_INFO(...)		::Bezel::Log::GetCoreLogger()->info(__VA_ARGS__)
#define BZ_CORE_WARN(...)		::Bezel::Log::GetCoreLogger()->warn(__VA_ARGS__)

/*
	MACRO DEFINITIONS CLIENT
*/
#define BZ_CLIENT_ERROR(...)	::Bezel::Log::GetClientLogger()->error(__VA_ARGS__)
#define BZ_CLIENT_TRACE(...)	::Bezel::Log::GetClientLogger()->trace(__VA_ARGS__)
#define BZ_CLIENT_FATAL(...)	::Bezel::Log::GetClientLogger()->fatal(__VA_ARGS__)
#define BZ_CLIENT_INFO(...)		::Bezel::Log::GetClientLogger()->info(__VA_ARGS__)
#define BZ_CLIENT_WARN(...)		::Bezel::Log::GetClientLogger()->warn(__VA_ARGS__)

/*
	EXTRA LOG CLASS NOTES:
	The original engine uses inline static for core and client functions, however my external
	application could not access the private pointers because of an expression error.
	I found a different approach using just static and employed it.
*/