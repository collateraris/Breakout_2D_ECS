#include <OGLML/Texture2D.h>

#include <glew.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <iostream>

using namespace oglml;

Texture2D::~Texture2D()
{

}

bool Texture2D::loadFromFile(const std::string& path, bool usingAlpha/* = false*/)
{
	GLuint textureID;
	glGenTextures(1, &textureID);

	int width = 0, height = 0, nrComponents;
	unsigned char* image = stbi_load(path.c_str(), &width, &height, &nrComponents, 0);
	if (image)
	{
		GLenum format;

		if (usingAlpha)
		{
			format = GL_RGBA;
		}
		else
		{
			format = GL_RGB;
		}
		

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		b_init = true;
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		b_init = false;
	}

	stbi_image_free(image);

	m_textureID = textureID;
	return b_init;
}

unsigned int Texture2D::GetTextureID()
{
	return m_textureID;
}

void Texture2D::operator=(Texture2D& texture)
{
	this->b_init = texture.b_init;
	this->m_textureID = texture.m_textureID;
}

