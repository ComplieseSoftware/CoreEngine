#pragma once
#include <cstdint>
#include <iostream>
#include <vector>

#include "shaders/src/Shader.h"
#include "vertex3D/vertex3D.h"
#include "textures/texture2D.h"

class Renderer {
public:
	void clear() const;
	void setClearColor(float R, float G, float B, float Alpha) const;

	void drawQuad(float x, float y, float width, float height, const Texture2D& texture, const Shader& shaderProgram);
	//void flush(const Texture2D& texture, const Shader& shaderProgram);

	void init();
private:
	uint32_t m_activeVBO{ 0 };
	uint32_t m_activeShader{ 0 };
	uint32_t m_activeTexture{ 0 };

	uint32_t m_VBO{}; // VBO(Vertex Buffer Object) - хранит все наши координаты для дальнейшего преобразования в вершины
	uint32_t m_VAO{}; // VAO (Vertex Array Object) — хранит настройки атрибутов вершин и связанные с ними VBO.
	uint32_t m_EBO{}; // EBO (Element Buffer Object) - хранит индексы вершин, чтобы OpenGL мог использовать их для построения фигур без дублирования одинаковых вершин.

	std::vector<uint32_t> m_indicesQuad = {
		0, 1, 2,
		0, 2, 3
	};
};