#pragma once
#include <memory>

#ifdef RZ_PLATFORM_WINDOWS
#if RZ_DYNAMIC_LINK
	#ifdef RZ_BUILD_DLL
		#define RAZOR_API __declspec(dllexport)
	#else 
		#define RAZOR_API __declspec(dllimport)
	#endif
#else
	#define RAZOR_API
#endif
#else
	#error RAZOR ONLY SUPPORTS WINDOWS!
#endif

#ifdef RZ_ENABLE_ASSERTS
	#define RZ_ASSERT(x, ...) {if(!(x)){ RZ_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }}
	#define RZ_CORE_ASSERT(x, ...) {if(!(x)){ RZ_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }}
#else
	#define RZ_ASSERT(x, ...)
	#define RZ_CORE_ASSERT(x, ...)
#endif

#define BIT(x)(1 << x)

#define RZ_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Razor
{
	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ...Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ...Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

}