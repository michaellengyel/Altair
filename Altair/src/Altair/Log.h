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
		inline static std::shared_ptr<spdlog::logger>& GetClientValLogger() { return s_ClientValLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
		static std::shared_ptr<spdlog::logger> s_ClientValLogger;
	};
	
}

#ifdef UNIT_TEST
	#define ALTAIR_LOG_INIT

	#define ALTAIR_CORE_TRACE
	#define ALTAIR_CORE_INFO
	#define ALTAIR_CORE_WARN
	#define ALTAIR_CORE_ERROR
	#define ALTAIR_CORE_FATAL

	#define ALTAIR_TRACE
	#define ALTAIR_INFO
	#define ALTAIR_WARN
	#define ALTAIR_ERROR
	#define ALTAIR_FATAL
#else
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
	// Core log macros
	#define ALTAIR_VAL_TRACE(...) ::Altair::Log::GetClientValLogger()->trace(__VA_ARGS__)
	#define ALTAIR_VAL_INFO(...) ::Altair::Log::GetClientValLogger()->info(__VA_ARGS__)
	#define ALTAIR_VAL_WARN(...) ::Altair::Log::GetClientValLogger()->warn(__VA_ARGS__)
	#define ALTAIR_VAL_ERROR(...) ::Altair::Log::GetClientValLogger()->error(__VA_ARGS__)
	#define ALTAIR_VAL_FATAL(...) ::Altair::Log::GetClientValLogger()->fatal(__VA_ARGS__)
#endif

