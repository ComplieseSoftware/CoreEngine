#pragma once

#include <glad/glad.h>
#include <cstdint>
#include <string>
#include <sstream>
#include <fstream>

#include "logger/Logger.h"

class Shader {
public:
	int init(const char* vertexPath, const char* fragmentPath);
	void use() const;

	uint32_t getID() const;

	void setBool(const std::string& name, bool value);
	void setInt(const std::string& name, int value);
	void setFloat(const std::string& name, float value);
private:
	uint32_t ID{};
};
