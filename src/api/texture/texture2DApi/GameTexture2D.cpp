#include "GameTexture2D.h"

#include "renderer/textures/Texture2D.h"
#include <string>

void GameTexture2D::setImage(const std::string& imgPath) {
	m_texture.loadTexture2D(imgPath);
	m_texture.imageFree2D();
}

void GameTexture2D::use() {
	m_texture.bindTexture2D();
}

void GameTexture2D::disable() {
	m_texture.disable();
}

const Texture2D& GameTexture2D::getTexture() const {
	return m_texture;
}