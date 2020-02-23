#pragma once

#ifdef ALTAIR_PLATFORM_WINDOWS
	#ifdef ALTAIR_BUILD_DLL
		#define ALTAIR_API __declspec(dllexport)
	#else
		#define ALTAIR_API __declspec(dllimport)
	#endif
#else
	#error Altair only supports Windows!
#endif