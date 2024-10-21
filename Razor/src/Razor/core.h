#pragma once

#ifdef RZ_PLATFORM_WINDOWS
	#ifdef RZ_BUILD_DLL
		#define RAZOR_API __declspec(dllexport)
	#else 
		#define RAZOR_API __declspec(dllimport)
	#endif
#else
	#error RAZOR ONLY SUPPORTS WINDOWS!
#endif
