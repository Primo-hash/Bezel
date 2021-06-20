#include "bezel/include/Log.h"

#include "spdlog/sinks/stdout_color_sinks.h"

namespace Bezel {

	// Initier Core og Client loggingspekere
	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;
	/*

		spdlog::logger* Log::GetCoreLogger()
		{
			static std::shared_ptr<spdlog::logger> s_CoreLogger =
				std::make_shared<spdlog::logger>(*spdlog::stdout_color_mt("BEZEL"));

			return s_CoreLogger.get();
		}

		spdlog::logger* Log::GetClientLogger()
		{
			static std::shared_ptr<spdlog::logger> s_ClientLogger =
				std::make_shared<spdlog::logger>(*spdlog::stdout_color_mt("APP"));

			return s_ClientLogger.get();
		}

	std::shared_ptr<spdlog::logger> Log::GetCoreLogger()
	{
		return s_CoreLogger;
	}

	std::shared_ptr<spdlog::logger> Log::GetClientLogger()
	{
		return s_ClientLogger;
	}
	*/

	void Bezel::Log::Init() {
		// Mulige meldings formateringer kan finnes her https://github.com/gabime/spdlog/wiki/3.-Custom-formatting
		// Sett formatet Farge>>Tidspunkt>>LoggerNavn>>LogMelding for log meldinger
		spdlog::set_pattern("%^[%T] %n: %v%$");
		s_CoreLogger = spdlog::stdout_color_mt("HAZEL");
		s_CoreLogger->set_level(spdlog::level::trace);

		s_ClientLogger = spdlog::stdout_color_mt("APP");
		s_ClientLogger->set_level(spdlog::level::trace);
	}

}