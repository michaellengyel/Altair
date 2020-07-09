#include "Log.h"

namespace Altair {

	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientValLogger;

	
	void Log::Init()
	{
		
		spdlog::set_pattern("%^[%T] %n: %v%$");

		s_CoreLogger = spdlog::stdout_color_mt("ALTAIR");
		s_CoreLogger->set_level(spdlog::level::trace);

		s_ClientLogger = spdlog::stdout_color_mt("SYSTEM");
		s_ClientLogger->set_level(spdlog::level::trace);

		s_ClientValLogger = spdlog::stdout_color_mt("VALIDATION");
		s_ClientValLogger->set_level(spdlog::level::trace);
	}
	
}