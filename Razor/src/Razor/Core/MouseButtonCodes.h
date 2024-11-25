#pragma once



#define RZ_MOUSE_BUTTON_1         0
#define RZ_MOUSE_BUTTON_2         1
#define RZ_MOUSE_BUTTON_3         2
#define RZ_MOUSE_BUTTON_4         3
#define RZ_MOUSE_BUTTON_5         4
#define RZ_MOUSE_BUTTON_6         5
#define RZ_MOUSE_BUTTON_7         6
#define RZ_MOUSE_BUTTON_8         7
#define RZ_MOUSE_BUTTON_LAST      RZ_MOUSE_BUTTON_8
#define RZ_MOUSE_BUTTON_LEFT      RZ_MOUSE_BUTTON_1
#define RZ_MOUSE_BUTTON_RIGHT     RZ_MOUSE_BUTTON_2
#define RZ_MOUSE_BUTTON_MIDDLE    RZ_MOUSE_BUTTON_3


namespace Razor
{
	using MouseCode = uint16_t;

	namespace Mouse
	{
		enum : MouseCode
		{
			// From glfw3.h
			Button0 = 0,
			Button1 = 1,
			Button2 = 2,
			Button3 = 3,
			Button4 = 4,
			Button5 = 5,
			Button6 = 6,
			Button7 = 7,

			ButtonLast = Button7,
			ButtonLeft = Button0,
			ButtonRight = Button1,
			ButtonMiddle = Button2
		};
	}
}