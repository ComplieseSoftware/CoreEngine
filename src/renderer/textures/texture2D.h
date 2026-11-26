#pragma once

#include <glad/glad.h>
#include <string>

#include "../../../Dependencies/stb_image/stb_image.h"
#include "logger/logger.h"

class Texture2D {
public:
	void loadTexture2D(const std::string& picPath);
	void imageFree2D() const;
	void bindTexture2D() const;
	void disable() const;

	int getTextureID() const;
private:
	uint32_t texture{};

	int width, height, nrChannels;
	unsigned char* data{};
};