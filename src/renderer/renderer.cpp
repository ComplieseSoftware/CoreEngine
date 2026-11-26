#include <glad/glad.h>
#include <cstdint>

#include "renderer.h"
#include "shaders/src/Shader.h"

void Renderer::init() {

	glGenVertexArrays(1, &m_VAO); //Также, как и с VBO(glGenBuffers) "регистрируем" VAO, как буффер, только вместо glGenBuffers, мы используем glGenVertexArrays
	glBindVertexArray(m_VAO); //Привязываем VAO, чтобы OpenGL сохранял в нём настройки атрибутов вершин

	glGenBuffers(1, &m_VBO); //Мы как бы "регистрируем" наш VBO, как буфер. В качестве 1-о параметра мы указываем - сколько буферов мы хотим создать, а во 2-ой параметр мы передаём наш VBO, чтобы он стал буфером и он мог работать с памятью видеокарты. VBO должен работать с память видеокарты напрямую, ради скорости
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO); //Активируем наш буфер VBO для работы. GL_ARRAY_BUFFER значит, что VBO работает с вершинами(Мы потом можем использовать другой буфер для работы, не только VBO, т.к эта функция переключает как раз эти буферы для работы с определенным типом буферных объектов). Теперь последующие обращения к GL_ARRAY_BUFFER будут связаны с нашим VBO

	glGenBuffers(1, &m_EBO); //"Регистрируем" EBO, как буффер

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO); //Привязываем EBO к GL_ELEMENT_ARRAY_BUFFER, чтобы OpenGL мог использовать EBO для работы с индексами вершин
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO); //Привязываем наш VBO, содержащий координаты вершин.

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), static_cast<void*>(0)); //Задаём парамтеры для xyz координат вершин
	glEnableVertexAttribArray(0); //Применяем атрибут 0
	/*
		1 параметр указывает, какой атрибут вершины мы хотим настроить. Мы указали в шейдере позицию атрибута вершин на 0(layout(location = 0) in vec3 aPos;), поэтому пишем 0
		2 параметр указывает размер нашего атрибута вершин(наш атрибут вершин является vec3), поэтому мы пишем 3
		3 параметр определяет тип данных: GL_FLOAT(В GLSL vec3 и другие vec представляют собой массив чисел в плавающий точкой)
		4 парметр указывает нужно ли нормализовать данные. Если мы работает с целочисленными типами данных, то указали бы GL_TRUE, но если мы работаем с числами с плавающей точкой, то стоит указать GL_FALSE
		5 параметр называется "шаг" и он указывает на расстояние между атрибутами вершин. У каждой вершины есть 3 значение: x, y, z. Значит размер одной врешины 3 * 4 = 12(4 это размер в байтах типа данных float), мы можем и просто написать 12, но если размер float изменится на другой платоформе, то нужно будет самостоятельно переписывать размеры данных
		6 параметр имеет тип void, поэтому требует приведения типа. Здесь мы указываем на позицию начала данных, т.к данные находятся в начале массива данных, это значение равно 0
	*/

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float))); //Задаём параметры для uv координат текстур
	glEnableVertexAttribArray(1); //Применяем атрибут 1
	
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indicesQuad.size() * sizeof(uint32_t), m_indicesQuad.data(), GL_STATIC_DRAW); //Заполняем EBO

	glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(Vertex3D), nullptr, GL_DYNAMIC_DRAW); //Заполняем VBO данными, мы будем динамически его менять для разных объектов
}

void Renderer::drawQuad(float x, float y, float width, float height, const Texture2D& texture, const Shader& shaderProgram) {
	Vertex3D vertices[4] = {
		{ x,         y,          0.0f, 0.0f, 0.0f }, // Угол 0 (Низ-Лево)
		{ x + width, y,          0.0f, 1.0f, 0.0f }, // Угол 1 (Низ-Право)
		{ x + width, y + height, 0.0f, 1.0f, 1.0f }, // Угол 2 (Верх-Право)
		{ x,         y + height, 0.0f, 0.0f, 1.0f }  // Угол 3 (Верх-Лево)
	};

	if (m_activeVBO != m_VBO) {
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		m_activeVBO = m_VBO;
	}

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); //ИМЕННО ОБНОВЛЯЕМ данные в наш VBO. Так как glBufferData полностью пересоздаёт буфер, а тут мы просто обновляем данные буфера 

	if (texture.getTextureID() != m_activeTexture) {
		texture.bindTexture2D();
		m_activeTexture = texture.getTextureID();
	}

	if (m_activeShader != shaderProgram.getID()) {
		shaderProgram.use(); //Активируем программу шейдеров. Теперь каждый шейдер и вызов отрисовки, после использования glUseProgram, будут использовать этот объект программы (и, следовательно, эти шейдеры)
		m_activeShader = shaderProgram.getID();
	}

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Renderer::clear() const {
	glClear(GL_COLOR_BUFFER_BIT); //Очищаем указанные буфера(в нашем случае это цветовой буфер)
}

void Renderer::setClearColor(float R, float G, float B, float Alpha) const {
	glClearColor(R, G, B, Alpha); //Задём, цвет которым будет очищаться цветовой буфер, т.е при очистки экрана мы будем получать этот цвет
}