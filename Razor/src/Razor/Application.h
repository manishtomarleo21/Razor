#pragma once

#include "core.h"

namespace Razor {

	class RAZOR_API Application
	{
	public:
		Application() {
		};
		virtual ~Application() {};

		void Run();
	};

	Application* CreateApplication();

	
}

