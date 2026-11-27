#include <glad/glad.h>
#include <string>

#include "stb_image/stb_image.h"

#include "texture2D.h"
#include "logger/Logger.h"

void Texture2D::loadTexture2D(const std::string& path) {
	data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0); // Load texture data

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Specify the data reading format (otherwise an access violation error will occur: memory could not be read)

	glGenTextures(1, &texture); // Create a texture object
	glBindTexture(GL_TEXTURE_2D, texture); // Bind the texture as GL_TEXTURE_2D since we are working with a 2D texture

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Configure texture wrapping. The 1st parameter specifies the texture target (2D, so GL_TEXTURE_2D), the 2nd specifies the option and axis to configure, and the 3rd sets the wrapping mode (we use standard repeating)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	if (data) {
		if (nrChannels == 3) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data); // Generate the texture
			/*
				1st parameter: specify the texture target (our texture is GL_TEXTURE_2D, so we use it here as well)
				2nd parameter: specify the mipmap level for which we want to create a texture; we leave it at the base level (0)
				3rd parameter: specify the format in which to store the texture (RGB in our case)
				4th and 5th parameters: specify the width and height of the texture
				6th parameter: should ALWAYS be 0 (legacy border parameter)
				7th and 8th parameters: specify the format and data type of the source image (we loaded the image with RGB values and stored them as chars / unsigned bytes)
				9th parameter: pass the actual image data (our `data` variable)

				After calling this function, our texture object (`texture`) has the texture image (`data`) attached to it.
			*/

			glGenerateMipmap(GL_TEXTURE_2D); // Generate mipmaps for our texture
			glBindTexture(GL_TEXTURE_2D, 0);
		}
		else if (nrChannels == 4) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data); // Generate the texture
			glGenerateMipmap(GL_TEXTURE_2D); // Generate mipmaps for our texture
			glBindTexture(GL_TEXTURE_2D, 0); // Disable texture
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