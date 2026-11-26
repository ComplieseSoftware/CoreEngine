#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

#include "logger/Logger.h"
#include "renderer/Renderer.h"
#include "renderer/window/WindowRenderer.h"
#include "renderer/textures/Texture2D.h"

#include "shaders/src/Shader.h"

#include "Dependencies/stb_image/stb_image.h"

//#define WIDTH 1680
//#define HEIGHT 920
//
//#define INTRODUCTION_VISIBLE //Закоментировать, если вы хотите отключить заставку
//
//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//void processInput();
void fixWorkingDirectory();
//
//enum currRender {
//	NONE,
//	TRI,
//	CUB,
//	LOADING,
//	GAME
//};

//static Renderer render{};
//static Window window{};
//
//static Shader gameShaders{};
//static Shader uiShaders{};
//
//static Texture2D textureBrick{};
//static Texture2D textureWood{};
//static Texture2D textureLoading{};
//
//static currRender currGameState{};
//static currRender curr{};
//
//static GLFWimage icon{};
//
//static bool blockInput{ false };

int main() {
	//fixWorkingDirectory();

	//int channels;
	//icon.pixels = stbi_load("materials/icon48x48.png", &icon.width, &icon.height, &channels, 0);

	//if (icon.pixels) {
	//	window.setIcon(icon);

	//	stbi_image_free(icon.pixels);
	//}
	//else {
	//	Logger::warn("Failed to load window icon");
	//}

	//render.init();

	//stbi_set_flip_vertically_on_load(true);

	//gameShaders.init("Shaders/vertex.vert", "Shaders/fragment.frag");
	//uiShaders.init("Shaders/vertexUI.vert", "Shaders/fragment.frag");

	//textureBrick.loadTexture2D("materials/brick.png");
	//textureBrick.imageFree2D();

	//textureWood.loadTexture2D("materials/wood.png");
	//textureWood.imageFree2D();

	//textureLoading.loadTexture2D("materials/loadingScreen.png");
	//textureLoading.imageFree2D();

	//render.setClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	//curr = currRender::LOADING;

	//while (!window.getShouldClose()) { //После каждой итерации проверяем, поступала ли команда о закрытии окна, если да, то выполняем функции в цикле:
	//	gameShaders.setFloat("screenHalf", (float)HEIGHT / WIDTH);
	//	render.clear();
	//	
	//	//processInput(); //Наша функция для обработки ввода

	//	#ifdef INTRODUCTION_VISIBLE
	//		if (curr == currRender::LOADING) {
	//			blockInput = true;

	//			float currentTime = glfwGetTime();
	//			static float loadingStartTime = glfwGetTime();
	//			float timePassed = currentTime - loadingStartTime;
	//			if (timePassed >= 3.0f) {
	//				textureLoading.disable();
	//				curr = currRender::CUB;
	//			} else {
	//				render.drawQuad(-1.0f, -1.0f, 2.0f, 2.0f, textureLoading, uiShaders);

	//				render.flush(textureLoading, uiShaders);
	//			}
	//		}
	//	#endif //INTRODUCTION_VISIBLE

	//	if (curr == currRender::CUB) {
	//		blockInput = false;
	//		render.drawQuad(0.0f, 0.0f, 0.5f, 0.5f, textureBrick, gameShaders);

	//		render.flush(textureBrick, gameShaders);
	//	}
	//	else if (curr == currRender::TRI) {
	//		blockInput = false;
	//	}

	//	window.swapBuffers(); //Меняем буфера(первый буфер это то, что мы видим сейчас, а второй это то, что мы должны будем увидеть на следующем кадре). Это нужно, чтобы пользователь не видел, то как мы отрисовываем кадр, а уже показывали заранее отрисованный кадр
	//	window.pollEvents(); //Проверяем, поступали ли какие-то события, например ввод с клавиаутры и т.д, обновляет состояние окна и вызывает соответствующие функции(которые можно зарегистрировать при помощи callback-методов)
	//}

	//window.close();

	//textureBrick.disable();
	//textureWood.disable();

	return 0;
}

void fixWorkingDirectory() {
	namespace fs = std::filesystem;

	// Если папки Shaders нет рядом с исполняемым файлом (запуск из x64/Debug или x64/Release)
	if (!fs::exists("Shaders")) {
		if (fs::exists("../../Shaders")) {
			fs::current_path("../../"); // Переключаем рабочую директорию на корень проекта
		}
		else if (fs::exists("../Shaders")) {
			fs::current_path("../");
		}
	}
}