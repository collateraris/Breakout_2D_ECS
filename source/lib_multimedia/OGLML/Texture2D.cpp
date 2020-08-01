#include <OGLML/Texture2D.h>

#include <glew.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <iostream>

using namespace oglml;

Texture2D::~Texture2D()
{

}

bool Texture2D::loadFromFile(const std::string& path)
{
	GLuint textureID;
	glGenTextures(1, &textureID);

	int width = 0, height = 0, nrComponents;
	unsigned char* image = stbi_load(path.c_str(), &width, &height, &nrComponents, 0);
	if (image)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
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

