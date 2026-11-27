#include "InputKeyboard.h"
#include "InputKeysKeyboard.h"
#include "logger/Logger.h"

#include <iostream>

bool InputKeyboard::isPressed(Key key) {
	if (m_window == nullptr) {
		Logger::fatal("Error");
		return false;
	}
	int inputKey = glfwGetKey(m_window->getWindow(), static_cast<int>(key));

	return inputKey == GLFW_PRESS;
}

void InputKeyboard::init(Window* window) {
	m_window = window;
}