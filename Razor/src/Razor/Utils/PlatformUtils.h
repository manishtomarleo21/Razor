#pragma once

#include <string>

namespace Razor
{
	class FileDialogs
	{
	public:
		//THese return empty string if cancelled
		static std::string OpenFile(const char* filter);
		static std::string SaveFile(const char* filter);
	};
}