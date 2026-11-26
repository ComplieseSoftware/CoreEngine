#pragma once

#include "renderer/textures/Texture2D.h"
#include <string>

class GameTexture2D {
public:
	const Texture2D& getTexture() const;

	void setImage(const std::string& imgPath);
	void use();
	void disable();
private:
	Texture2D m_texture{};
};