#pragma once
#include <string>
#include <format>
#include <functional>
#include <cstdint>

#include "logger/Logger.h"
#include "config/Config.h"
#include "renderer/window/WindowRenderer.h"
#include "renderer/Renderer.h"
#include "renderer/textures/Texture2D.h"
#include "input/Keyboard/InputKeyboard.h"

class Application {
public:
	Application() : m_width(900), m_height(600), m_appName(Config::engineName), m_isVisibleIntroduction(true) {};

	Application(int aWidth, int aHeight, const std::string& aName, bool aIntro);

	void run(); //Call this function if you want to open window
	void close(); //Call this function if you want to close window
	void setIcon(const std::string& icoPath); //Enter a path to .ico file

	void render(const float x, const float y, const float width, const float height, const Texture2D& texture); //Render Quad
	
	float getDeltaTime() const; //Get delta time

	void setUpdateCallBack(std::function<void(float)> func); //This function set func to callback object
	void setRenderCallBack(std::function<void()> func);
	void setInputCallBack(std::function<void()> func);
	void setInitCallBack(std::function<void()> func);

	void setBackgroundColor(float R, float G, float B, float Alpha);
private:
	enum class RenderState {
		LOADING,
		GAME
	};

	uint16_t m_width{};
	uint16_t m_height{};

	float m_dt{};

	float m_R{};
	float m_G{};
	float m_B{};
	float m_Alpha{};

	std::string m_appName{};

	std::function<void(float)> m_updateCallBack{ nullptr };
	std::function<void()> m_renderCallBack{ nullptr };
	std::function<void()> m_inputCallBack{ nullptr };
	std::function<void()> m_initCallBack{ nullptr };

	Renderer m_render{};
	Window m_window{};
	RenderState m_currRender{};

	Shader m_gameShaders{};
	Shader m_uiShaders{};
	Shader* m_currShader{ nullptr };

	Texture2D m_textureLoading{};

	bool m_isVisibleIntroduction{};
};