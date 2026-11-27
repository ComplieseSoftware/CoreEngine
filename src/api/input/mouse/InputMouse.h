#pragma once

#include "InputKeysMouse.h"
#include "logger/Logger.h"
#include "renderer/window/WindowRenderer.h"

class InputMouse {
private:
	inline static Window* m_window{};
public:
	static bool isPressed(MouseButton key);
	static void init(Window* window);

	static float getNormalizedMouseX();
	static float getNormalizedMouseY();
};