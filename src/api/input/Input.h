#pragma once

#include "InputKeys.h"
#include "logger/Logger.h"
#include "renderer/window/WindowRenderer.h"

class Input {
private:
	inline static Window* m_window{};
public:
	static bool isPressed(Key key);
	static void init(Window* window);
};