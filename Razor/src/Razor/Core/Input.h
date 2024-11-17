#pragma once

#include "Razor/Core/KeyCodes.h"
//#include "Razor/Core/MouseCodes.h"
#include "Razor/Core/core.h"

//#include <glm/glm.hpp>

namespace Razor {

	class RAZOR_API Input
	{
	public:
		static bool IsKeyPressed(int keycode);
		static bool IsMouseButtonPressed(int button);
		static std::pair<float, float>GetMousePosition();

		static float GetMouseX();
		static float GetMouseY();
	
	};
}
