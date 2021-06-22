#include "bezel/Precompiled.h"
#include "bezel/include/Log.h"

namespace Bezel {

	// Initier Core og Client loggingspekere
	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

	void Bezel::Log::init() {
		// Mulige meldings formateringer kan finnes her https://github.com/gabime/spdlog/wiki/3.-Custom-formatting
		// Sett formatet Farge>>Tidspunkt>>LoggerNavn>>LogMelding for log meldinger
		spdlog::set_pattern("%^[%T] %n: %v%$");
		s_CoreLogger = spdlog::stdout_color_mt("BEZEL");
		s_CoreLogger->set_level(spdlog::level::trace);

		s_ClientLogger = spdlog::stdout_color_mt("APP");
		s_ClientLogger->set_level(spdlog::level::trace);
	}

}