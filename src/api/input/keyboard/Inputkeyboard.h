#pragma once

#include "InputKeysKeyboard.h"
#include "logger/Logger.h"
#include "renderer/window/WindowRenderer.h"

class InputKeyboard {
private:
	inline static Window* m_window{};
public:
	static bool isPressed(Key key);
	static void init(Window* window);
};