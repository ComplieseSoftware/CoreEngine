#include "InputMouse.h"
#include "InputKeysMouse.h"
#include "logger/Logger.h"
#include "config/Config.h"

#include <iostream>

bool InputMouse::isPressed(MouseButton key) {
	if (m_window == nullptr) {
		Logger::fatal("Error. The Core Engine window object has not been set, or it has become `nullptr` due to unexpected actions.");
		return false;
	}
	int inputKey = glfwGetMouseButton(m_window->getWindow(), static_cast<int>(key));

	return inputKey == GLFW_PRESS;
}

void InputMouse::init(Window* window) {
	m_window = window;
}

float InputMouse::getNormalizedMouseX() {
	if (m_window == nullptr) {
		Logger::fatal("Error. The Core Engine window object has not been set, or it has become `nullptr` due to unexpected actions.");
		return 0.0f;
	}

	double x, y;
	glfwGetCursorPos(m_window->getWindow(), &x, &y);

	float aspect = static_cast<float>(Config::width) / static_cast<float>(Config::height);
	return ((static_cast<float>(x) / Config::width) * 2.0f - 1.0f) * aspect;
}

float InputMouse::getNormalizedMouseY() {
	if (m_window == nullptr) {
		Logger::fatal("Error. The Core Engine window object has not been set, or it has become `nullptr` due to unexpected actions.");
		return 0.0f;
	}

	double x, y;
	glfwGetCursorPos(m_window->getWindow(), &x, &y);

	return 1.0f - (static_cast<float>(y) / Config::height) * 2.0f;
}
