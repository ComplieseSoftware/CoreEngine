#include <glad/glad.h>
#include <cstdint>
#include <string>
#include <sstream>
#include <fstream>

#include "Shader.h"
#include "logger/logger.h"

int Shader::init(const char* vertexPath, const char* fragmentPath) {
	std::string vertexCode;
	std::string fragmentCode;

	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try {
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);

		std::stringstream vShaderStream;
		std::stringstream fShaderStream;

		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		vShaderFile.close();
		fShaderFile.close();

		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ios_base::failure& e) {
		Logger::fatal("CORE_ENGINE -> ERROR -> SHADER -> SHADER_FILE_NOT_SUCCESFULLY_READ");
	}

	const char* vShaderCode{ vertexCode.c_str() };
	const char* fShaderCode{ fragmentCode.c_str() };

	//Тут мы будем проверять компиляцию и линковку(далее в коде) шейдеров
	int success; //Число, которое будет указывать на успех
	char infoLog[512]; //Массив char для лога

	uint32_t vertexShader;
	uint32_t fragmentShader;

	vertexShader = glCreateShader(GL_VERTEX_SHADER); //Здесь мы указываем GL_VERTEX_SHADER, т.к мы работаем с вершинным шейдером
	glShaderSource(vertexShader, 1, &vShaderCode, NULL); //Приклрепляем исходный код шейдера к объекту шейдера. В 1-ом аргументе передаём объект шейдера, во 2-ом указываем, сколько строк кода мы передаём в качестве исходного кода(в нашем случае одна строка), в 3-ем передаём сам исходный код, через ссылку для экономии памяти, 4-ый можем поставить, как NULL
	glCompileShader(vertexShader); //Компилируем шейдер

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success); //Проверяем компилцию

	if (!success) {
		glGetShaderInfoLog(vertexShader, sizeof(infoLog), NULL, infoLog); //Выводим соощения компилятора GLSL

		Logger::fatal("CORE_ENGINE -> ERROR -> SHADER -> VERTEX_SHADER -> COMPILATION_FAILED");
		Logger::fatal("Failed to compile vertex shader");
		Logger::info(infoLog); //Логгируем ошибки

		return -1;
	}

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); //Здесь мы указываем GL_FRAGMENT_SHADER, т.к мы работаем с фрагментным шейдером
	glShaderSource(fragmentShader, 1, &fShaderCode, NULL); //Приклрепляем исходный код шейдера к объекту шейдера. В 1-ом аргументе передаём объект шейдера, во 2-ом указываем, сколько строк кода мы передаём в качестве исходного кода(в нашем случае одна строка), в 3-ем передаём сам исходный код, через ссылку для экономии памяти, 4-ый можем поставить, как NULL
	glCompileShader(fragmentShader); //Компилируем наш шейдер

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success); //Проверяем стату компиляции

	if (!success) {
		glGetShaderInfoLog(fragmentShader, sizeof(infoLog), NULL, infoLog);

		Logger::fatal("CORE_ENGINE -> ERROR -> SHADER -> FRAGMENT_SHADER -> COMPILATION_FAILED");
		Logger::fatal("Failed to compile fragment shader");
		Logger::info(infoLog); //Логгируем ошибки

		return -1;
	}

	ID = glCreateProgram(); //Создаём окончательную объединёную версию шейдеров(программу шейдеров). Это нужно, чтобы OpenGL мог использовать наши шейдеры для дальнейшей отрисовки
	glAttachShader(ID, vertexShader); //Кладём в программу шейдеров наш вершинный шейдер
	glAttachShader(ID, fragmentShader); //Кладём в программу шейдеров наш фрагментный шейдер
	glLinkProgram(ID); //Объединяем всё в одну программу шейдеров

	glGetProgramiv(ID, GL_LINK_STATUS, &success); //Проверяем успех линковки(объединения шейдеров в одну программу). Здесь процесс похож с проверкой компиляции шейдеров, только используем вместо glGetShaderiv - glGetProgramiv и нам нужен статус линковки, поэтому GL_LINK_STATUS

	if (!success) {
		glGetProgramInfoLog(ID, sizeof(infoLog), NULL, infoLog);
		glDeleteProgram(ID);

		Logger::fatal("CORE_ENGINE -> ERROR -> SHADER_PROGRAM -> LINK -> LINKING_FAILED");
		Logger::fatal("Failed to link shaders to shader program");
		Logger::info(infoLog); //Логгируем ошибки

		return -1;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	//Мы это делаем, чтобы освободить память видеокарты, т.к наши шейдеры уже записаны в нашу программу и нам не нужно больше их хранить по отдельности
	//Есть также функция glDeleteProgram(). Она нужна, чтобы удалить именно программу, но нам нужно удалить именно шейдеры по отдельности. То есть наши шейдеры по-отдельности нам больше не понадобятся, они выполнили свою задачу - быть записаными в программу шейдеров

	return 0;
}

void Shader::use() const {
	glUseProgram(ID);
}

uint32_t Shader::getID() const {
	return ID;
}

void Shader::setBool(const std::string& name, bool value) {
	glUniform1i(glGetUniformLocation(ID, name.c_str()), static_cast<int>(value));
}

void Shader::setInt(const std::string& name, int value) {
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) {
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}