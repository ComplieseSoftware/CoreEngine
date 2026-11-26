#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

class Window {
public:
	void init(const int width, const int height, const std::string& title);
	void swapBuffers();
	void pollEvents();
	void setShouldClose(const bool shClose);
	void close();
	void setIcon(const std::string& iconPath);

	GLFWwindow* getWindow() const;

	bool getShouldClose() const;

private:
	GLFWwindow* m_window{ nullptr };
};