#include <string>
#include <iostream>

#include "Application.h"
#include "logger/Logger.h"
#include "config/Config.h"
#include "renderer/window/WindowRenderer.h"
#include "renderer/Renderer.h"
#include "input/keyboard/InputKeyboard.h"
#include "input/mouse/InputMouse.h"
#include "shaders/src/Shader.h"
#include "audioEngine/2DAudioEngine/AudioEngine2D.h"

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
	m_window.init(m_width, m_height, m_appName); // Initialize the window
	m_render.init(); // Initialize the renderer

	InputKeyboard::init(&m_window); // Initialize keyboard input
	InputMouse::init(&m_window); // Initialize mouse input

	AudioEngine2D::init(); // Initialize the audio engine

	stbi_set_flip_vertically_on_load(true); // Flip textures vertically on load

	m_gameShaders.init("Shaders/vertex.vert", "Shaders/fragment.frag"); // Initialize the game shader
	m_uiShaders.init("Shaders/vertexUI.vert", "Shaders/fragment.frag"); // Initialize the UI shader

	m_textureLoading.loadTexture2D("materials/loadingScreen.png"); // Load the loading screen texture
	m_textureLoading.imageFree2D(); // Free texture memory

	double lastTime = glfwGetTime();
	double loadingStartTime = glfwGetTime();

	if (m_isVisibleIntroduction == false) { // Check if the splash screen is enabled
		m_currRender = RenderState::GAME; // if no, launch the game immediately
	} 
	else {
		m_currRender = RenderState::LOADING; // If yes, launch the splash screen
	}

	if (m_initCallBack != nullptr) { 
		m_initCallBack(); // Retrieve initialization data from the developer's game
	}

	m_render.setClearColor(m_R, m_G, m_B, m_Alpha); // Set the background color

	while (!m_window.getShouldClose()) { // After each iteration, check if a command to close the window was received; if so, execute the functions in the loop:
		m_gameShaders.setFloat("screenHalf", (float)m_height / m_width); // Pass a parameter to the shader to prevent horizontal stretching
		m_render.clear(); // Clear the screen

		double currentTime = glfwGetTime();
		m_dt = static_cast<float>(currentTime - lastTime); // Get deltaTime

		lastTime = currentTime;

		if (m_isVisibleIntroduction) {
			if (m_currRender == RenderState::LOADING) { // Start rendering the splash screen
				m_currShader = &m_uiShaders; // Set the UI shader as the current shader

				float currentTime = glfwGetTime();

				if (currentTime - loadingStartTime >= 3.0f) {
					m_textureLoading.disable(); // Disable the texture after 3 seconds have passed
					m_currRender = RenderState::GAME; // Start the game
					Logger::info("Success");
				}
				else {
					m_render.drawQuad(-1.0f, -1.0f, 2.0f, 2.0f, m_textureLoading, *m_currShader); // Render the splash screen
				}
			}
		}

		if (m_currRender == RenderState::GAME) { // If we are in the game
			m_currShader = &m_gameShaders; // Set the game shader as the current shader

			if (m_inputCallBack != nullptr) { // Receive the game input function
				m_inputCallBack();
			}

			if (m_updateCallBack != nullptr) { // Receive game updates
				m_updateCallBack(m_dt);
			}

			if (m_renderCallBack != nullptr) { // Receive the game renderer
				m_renderCallBack();
			}
		}

		m_window.swapBuffers(); // Swap the buffers (the front buffer is what we currently see, and the back buffer is what will be displayed on the next frame). This prevents the user from seeing the frame being drawn in real time, showing a pre-rendered frame instead
		m_window.pollEvents(); // Check if any events were triggered (such as keyboard input, etc.), update the window state, and invoke the corresponding functions (which can be registered via callback methods)
	}

	m_window.close(); // Close the window if a close request has been triggered
}

void Application::close() {
	AudioEngine2D::shutdown();
	m_window.setShouldClose(true);
}

void Application::render(const float x, const float y, const float width, const float height, const Texture2D& texture) {
	m_render.drawQuad(x, y, width, height, texture, *m_currShader);
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
	return m_dt;
}

void Application::setBackgroundColor(float R, float G, float B, float Alpha) {
	m_R = R;
	m_G = G;
	m_B = B;
	m_Alpha = Alpha;
}