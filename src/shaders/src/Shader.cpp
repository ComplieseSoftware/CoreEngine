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

	// Here we will check shader compilation and linking (later in the code)
	int success; // Integer flag indicating whether the operation succeeded
	char infoLog[512]; // Char array to store the info log

	uint32_t vertexShader;
	uint32_t fragmentShader;

	vertexShader = glCreateShader(GL_VERTEX_SHADER); // Here we specify GL_VERTEX_SHADER because we are working with a vertex shader
	glShaderSource(vertexShader, 1, &vShaderCode, NULL); // Attach the shader source code to the shader object. The 1st argument is the shader object, the 2nd specifies how many strings we are passing as source code (one string in our case), the 3rd passes the source code itself by pointer to save memory, and the 4th can be set to NULL
	glCompileShader(vertexShader); //Compile the shader

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success); // Check if the vertex shader compiled successfully

	if (!success) {
		glGetShaderInfoLog(vertexShader, sizeof(infoLog), NULL, infoLog); // Output GLSL compiler messages

		Logger::fatal("CORE_ENGINE -> ERROR -> SHADER -> VERTEX_SHADER -> COMPILATION_FAILED");
		Logger::fatal("Failed to compile vertex shader");
		Logger::info(infoLog); // Log errors

		return -1;
	}

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); // Here we specify GL_FRAGMENT_SHADER because we are working with a fragment shader
	glShaderSource(fragmentShader, 1, &fShaderCode, NULL); // Attach the shader source code to the shader object. The 1st argument is the shader object, the 2nd specifies how many strings we are passing as source code (one string in our case), the 3rd passes the source code itself by pointer to save memory, and the 4th can be set to NULL
	glCompileShader(fragmentShader); // Compile our shader

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success); // Check shader compilation status

	if (!success) {
		glGetShaderInfoLog(fragmentShader, sizeof(infoLog), NULL, infoLog);

		Logger::fatal("CORE_ENGINE -> ERROR -> SHADER -> FRAGMENT_SHADER -> COMPILATION_FAILED");
		Logger::fatal("Failed to compile fragment shader");
		Logger::info(infoLog); // Log errors

		return -1;
	}

	ID = glCreateProgram(); // Create the final linked shader program. This allows OpenGL to use our shaders for subsequent rendering
	glAttachShader(ID, vertexShader); // Attach the vertex shader to the shader program
	glAttachShader(ID, fragmentShader); // Attach the fragment shader to the shader program
	glLinkProgram(ID); // Link everything into a single shader program

	glGetProgramiv(ID, GL_LINK_STATUS, &success); // Check if linking (combining the shaders into a single program) succeeded. The process is similar to checking shader compilation, except we use glGetProgramiv instead of glGetShaderiv and check GL_LINK_STATUS for the linking status

	if (!success) {
		glGetProgramInfoLog(ID, sizeof(infoLog), NULL, infoLog);
		glDeleteProgram(ID);

		Logger::fatal("CORE_ENGINE -> ERROR -> SHADER_PROGRAM -> LINK -> LINKING_FAILED");
		Logger::fatal("Failed to link shaders to shader program");
		Logger::info(infoLog); // Log errors

		return -1;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	// We do this to free GPU memory, since our shaders are already linked into the program and we no longer need to keep them separately
	// There is also glDeleteProgram(), which deletes the entire program, whereas we only want to delete the individual shader objects. In other words, we don't need the separate shaders anymore—they've served their purpose of being compiled and linked into the shader program

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