#include <glad/glad.h>
#include <string>

#include "../Dependencies/stb_image/stb_image.h"

#include "texture2D.h"
#include "logger/Logger.h"

void Texture2D::loadTexture2D(const std::string& path) {
	data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0); //Загружаем данные текстуры

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); //Указываем формат чтения данных(иначе будет ошибка, что память не может read)

	glGenTextures(1, &texture); //Создаём объект текстуры
	glBindTexture(GL_TEXTURE_2D, texture); //Регистрируем текстуру, как GL_TEXTURE_2D, т.к у нас 2D текстура

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //Настраиваем сэмоплирование текстур. В первом парамтеры указываем с какими текстурами мы работаем(2D, поэтому GL_TEXTURE_2D), во 2-м указываем какую опцию и для какой оси мы хотим настроить, в 3-ем указываем режим повторения текстуры(У нас обычное повторение)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	if (data) {
		if (nrChannels == 3) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data); //Создаём саму текстуру:
			/*
				В 1-м праметре указываем целевую текстуру(наша текстура GL_TEXTURE_2D, поэтому и здесь также)
				Во 2-м параметре определяем уровень мип-карты, для которого мы хотим создать текстуру, мы оставим его на базовом уровне(0)
				В 3-ем указываем в каком формате хранить текстуру, у нас это RGB
				В 4-ом и 5-м параметре указываем ширину и длину текстуры
				В 6-м параметре ВСЕГДА должно быть 0
				В 7-м и 8-м параметре формат и тип данных исходного изображения(мы загрузили изображение с использованием значений RGB и сохранили их в виде символов(беззнаковых байт)
				в 9-м параметре указываем фактические данные изображения(у нас это переменная data)

				После вызова этой функции наш объект текстуры(texture) связан с изображением текстуры(data)
			*/
			glGenerateMipmap(GL_TEXTURE_2D); //Генерируем мип-карту для нашей текстуры
			glBindTexture(GL_TEXTURE_2D, 0);
		}
		else if (nrChannels == 4) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data); //Создаём саму текстуру
			glGenerateMipmap(GL_TEXTURE_2D); //Генерируем мип-карту для нашей текстуры
			glBindTexture(GL_TEXTURE_2D, 0); //Отключаем нашу текстуру
		}
	}
	else {
		Logger::error("Failed to load texture");
	}
}

void Texture2D::imageFree2D() const {
	stbi_image_free(data);
}

void Texture2D::bindTexture2D() const {
	glBindTexture(GL_TEXTURE_2D, texture);
}

void Texture2D::disable() const {
	glDeleteTextures(0, &texture);
}

int Texture2D::getTextureID() const {
	return texture;
}