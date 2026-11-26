#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string_view>

#include "logger/logger.h"
#include "windowRenderer.h"
#include "stb_image/stb_image.h"

void framebuffer_size_callback(GLFWwindow* window, const int width, const int height);

void Window::init(const int width, const int height, const std::string& title) {
	// Далее мы будем настраивать GLFW к работе:
	Logger::init("", true); //Инициализируем логгер

	if (!glfwInit()) { //Инициализируем и проверяем GLFW
		Logger::fatal("Failed to initialize GLFW");

		throw std::runtime_error("Failed to initialize GLFW");
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // Указываем число, перед точкой: версии OpenGL, которую мы используем(у нас OpenGL 3.3)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // Повторяем то же самое, только указываем число, после точки, если бы использовали версию 3.4, то здесь было б 4, а не 3
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Указываем, что GLFW должен убрать из нашей работы устаревшие функции OpenGl(ограничить)
	//Мы закончили настройку GLFW

	m_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr); //Создаём окно(используем указатель, т.к окно может не создаться и для дальнейшей проверки на nullptr)

	if (m_window == nullptr) { //Проверяем создалось ли окно
		Logger::fatal("Failed to create a GLFW Window");

		glfwTerminate(); //Уничтожаем GLFW(программу)
		throw std::runtime_error("Failed to create a GLFW Window");
	}

	glfwMakeContextCurrent(m_window); //Сообщаем, что наш window будет основным контекстом в текущем потоке

	glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback); //Когда например пользователь растягивает окно, мы автоматически меняем область видимости, чтобы не было чёрных частей

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) { // Проверяем инициализацию GLAD
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
	return m_window;
}

void framebuffer_size_callback(GLFWwindow* window, const int width, const int height) { //Функция нужна для того, чтобы автоматически изменять glViewport, если пользователь изменит размеры окна
	glViewport(0, 0, width, height); //Указывыем OpenGl размеры нашего окна, чтобы он знал, как мы хотим отобразить координаты относительно окна. В первых двух параметрах, мы указываем положение нижнего левого угла окна. В последних двух, мы указываем ширину и высоту окна в пикселях(просто тавим значения из нашего window)
	//Мы бы могли указать более меньшие размеры окна, тогда бы вся отрисовка отображалась в боле маленьком окне
}