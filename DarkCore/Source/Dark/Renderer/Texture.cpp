#include "dkpch.h"
#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Dark/Core.h"

namespace Dark
{
	Texture::Texture(std::string source, bool alpha)
	{
		this->source = source;
		this->alpha = alpha;
		m_texture = 0;

		stbi_set_flip_vertically_on_load(1);

		glGenTextures(1, &m_texture);
		glBindTexture(GL_TEXTURE_2D, m_texture);
		// set the texture wrapping parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		// load image, create texture and generate mipmaps
		int width, height, nrChannels;
		// The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.

		int rgb = GL_RGB;
		if (alpha == true)
		{
			rgb = GL_RGBA;
		}

		unsigned char* data = stbi_load(source.c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, rgb, width, height, 0, rgb, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			Logger::error("Failed to load texture");
		}
		stbi_image_free(data);
	}

	void Texture::Bind(int unit)
	{
		glBindTextureUnit(unit, m_texture);
	}
}
