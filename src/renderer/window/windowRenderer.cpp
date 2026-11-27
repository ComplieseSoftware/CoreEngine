#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string_view>

#include "logger/logger.h"
#include "windowRenderer.h"
#include "stb_image/stb_image.h"

void framebuffer_size_callback(GLFWwindow* window, const int width, const int height);

void Window::init(const int width, const int height, const std::string& title) {
	// Next, we will configure GLFW:
	Logger::init("", true); // Initialize the logger

	if (!glfwInit()) { // Initialize and verify GLFW
		Logger::fatal("Failed to initialize GLFW");

		throw std::runtime_error("Failed to initialize GLFW");
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // Specify the major version number (before the decimal point) of the OpenGL version we are using (we are using OpenGL 3.3)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // Repeat the same, but specify the minor version number (after the decimal point)—for example, for version 3.4, this would be 4 instead of 3
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Instruct GLFW to exclude deprecated OpenGL functions (restrict to core profile)
	//Мы закончили настройку GLFW

	m_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr); // Create the window (use a pointer because creation may fail, allowing us to check for nullptr later)

	if (m_window == nullptr) { // Check if the window was created
		Logger::fatal("Failed to create a GLFW Window");

		glfwTerminate(); // Terminate GLFW (shut down the program)
		throw std::runtime_error("Failed to create a GLFW Window");
	}

	glfwMakeContextCurrent(m_window); // Set our window as the main OpenGL context on the current thread

	glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback); // When the user resizes the window, automatically adjust the viewport to avoid black bars

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) { // Check GLAD initialization
		Logger::fatal("Failed to initialize GLAD");
		glfwTerminate();

		throw std::runtime_error("Failed to create a GLFW Window");
	}
}

bool Window::getShouldClose() const {
	return glfwWindowShouldClose(m_window);
}

void Window::swapBuffers() {
	glfwSwapBuffers(m_window);
}

void Window::pollEvents() {
	glfwPollEvents();
}

void Window::setShouldClose(const bool isClose) {
	glfwSetWindowShouldClose(m_window, isClose);
}

void Window::close() {
	glfwTerminate();
}

void Window::setIcon(const std::string& iconPath) {
	GLFWimage icon;

	int channels;
	icon.pixels = stbi_load("materials/icon48x48.png", &icon.width, &icon.height, &channels, 0);

	if (icon.pixels) {
		glfwSetWindowIcon(m_window, 1, &icon);
		stbi_image_free(icon.pixels);
	}
	else {
		Logger::warn("Failed to load window icon");
	}
}

GLFWwindow* Window::getWindow() const {
	if (m_window == nullptr) {
		Logger::fatal("Window wasn't initialized");
	}
	else {
		return m_window;
	}
}

void framebuffer_size_callback(GLFWwindow* window, const int width, const int height) { // Callback function to automatically update glViewport whenever the user resizes the window
	glViewport(0, 0, width, height); // Tell OpenGL the dimensions of our window so it knows how to map coordinates relative to the window. The first two parameters set the location of the lower-left corner, and the last two specify the width and height in pixels (we simply pass the values from our window)
	// We could specify smaller dimensions, in which case all rendering would appear within a smaller area of the window
}