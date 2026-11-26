#include <string>
#include <iostream>

#include "Application.h"
#include "logger/Logger.h"
#include "config/Config.h"
#include "renderer/window/WindowRenderer.h"
#include "renderer/Renderer.h"
#include "input/Input.h"
#include "shaders/src/Shader.h"

Application::Application(int aWidth, int aHeight, const std::string& aName, bool aIntro) : m_width(aWidth), m_height(aHeight), m_appName(aName), m_isVisibleIntroduction(aIntro) {
	if (aWidth < 128 || aHeight < 128) {
		Logger::fatal("The height or table setting has been set lower than is permissible");
		return;
	}

	if (aName.empty()) {
		Logger::warn(std::format("Window name not set. Therefore, the default name will be used: {}", Config::engineName));
		m_appName = Config::engineName;
	}
};

void Application::run() {
	m_window.init(m_width, m_height, m_appName);
	m_render.init();

	Input::init(&m_window);

	stbi_set_flip_vertically_on_load(true);

	m_gameShaders.init("Shaders/vertex.vert", "Shaders/fragment.frag");
	m_uiShaders.init("Shaders/vertexUI.vert", "Shaders/fragment.frag");

	m_textureLoading.loadTexture2D("materials/loadingScreen.png");
	m_textureLoading.imageFree2D();

	m_render.setClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	double lastTime = glfwGetTime();
	double loadingStartTime = glfwGetTime();

	if (m_isVisibleIntroduction == false) {
		m_currRender = RenderState::GAME;
	} 
	else {
		m_currRender = RenderState::LOADING;
	}

	if (m_initCallBack != nullptr) {
		m_initCallBack();
	}

	while (!m_window.getShouldClose()) { //После каждой итерации проверяем, поступала ли команда о закрытии окна, если да, то выполняем функции в цикле:
		m_gameShaders.setFloat("screenHalf", (float)m_height / m_width);
		m_render.clear();

		double currentTime = glfwGetTime();
		dt = static_cast<float>(currentTime - lastTime);

		lastTime = currentTime;

		if (m_isVisibleIntroduction) {
			if (m_currRender == RenderState::LOADING) {
				m_currShader = m_uiShaders;
				m_blockInput = true;

				float currentTime = glfwGetTime();

				if (currentTime - loadingStartTime >= 30.0f) {
					m_textureLoading.disable();
					m_currRender = RenderState::GAME;
					Logger::info("Success");
				}
				else {
					m_render.drawQuad(-1.0f, -1.0f, 2.0f, 2.0f, m_textureLoading, m_currShader);
				}
			}
		}

		if (m_currRender == RenderState::GAME) {
			m_currShader = m_gameShaders;

			if (m_inputCallBack != nullptr) {
				m_inputCallBack();
			}

			if (m_updateCallBack != nullptr) {
				m_updateCallBack(dt);
			}

			if (m_renderCallBack != nullptr) {
				m_renderCallBack();
			}
		}

		m_window.swapBuffers(); //Меняем буфера(первый буфер это то, что мы видим сейчас, а второй это то, что мы должны будем увидеть на следующем кадре). Это нужно, чтобы пользователь не видел, то как мы отрисовываем кадр, а уже показывали заранее отрисованный кадр
		m_window.pollEvents(); //Проверяем, поступали ли какие-то события, например ввод с клавиаутры и т.д, обновляет состояние окна и вызывает соответствующие функции(которые можно зарегистрировать при помощи callback-методов)
	}

	m_window.close();
}

void Application::close() {
	m_window.setShouldClose(true);
}

void Application::render(const float x, const float y, const float width, const float height, const Texture2D& texture) {
	m_render.drawQuad(x, y, width, height, texture, m_currShader);
}

void Application::setIcon(const std::string& icoPath) {
	stbi_set_flip_vertically_on_load(false);
	m_window.setIcon(icoPath);
	stbi_set_flip_vertically_on_load(true);
}

void Application::setUpdateCallBack(std::function<void(float)> func) {
	m_updateCallBack = func;
}

void Application::setInputCallBack(std::function<void()> func) {
	m_inputCallBack = func;
}

void Application::setRenderCallBack(std::function<void()> func) {
	m_renderCallBack = func;
}

void Application::setInitCallBack(std::function<void()> func) {
	m_initCallBack = func;
}

float Application::getDeltaTime() const {
	return dt;
}