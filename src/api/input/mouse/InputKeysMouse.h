#pragma once
#include <cstdint>

enum class MouseButton : uint16_t {
	Button1 = 0,
	Button2 = 1,
	Button3 = 2,
	Button4 = 3,
	Button5 = 4,
	Button6 = 5,
	Button7 = 6,
	Button8 = 7,

	LAST = Button8,
	LEFT = Button1,
	RIGHT = Button2,
	MIDDLE = Button3
};
