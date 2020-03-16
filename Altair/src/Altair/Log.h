#pragma once

#include <memory>

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Altair {

	class ALTAIR_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
	
}
// Init functon
#define ALTAIR_LOG_INIT Altair::Log::Init()

// Core log macros
#define ALTAIR_CORE_TRACE(...) ::Altair::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define ALTAIR_CORE_INFO(...) ::Altair::Log::GetCoreLogger()->info(__VA_ARGS__)
#define ALTAIR_CORE_WARN(...) ::Altair::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define ALTAIR_CORE_ERROR(...) ::Altair::Log::GetCoreLogger()->error(__VA_ARGS__)
#define ALTAIR_CORE_FATAL(...) ::Altair::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Core log macros
#define ALTAIR_TRACE(...) ::Altair::Log::GetClientLogger()->trace(__VA_ARGS__)
#define ALTAIR_INFO(...) ::Altair::Log::GetClientLogger()->info(__VA_ARGS__)
#define ALTAIR_WARN(...) ::Altair::Log::GetClientLogger()->warn(__VA_ARGS__)
#define ALTAIR_ERROR(...) ::Altair::Log::GetClientLogger()->error(__VA_ARGS__)
#define ALTAIR_FATAL(...) ::Altair::Log::GetClientLogger()->fatal(__VA_ARGS__)