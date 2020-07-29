#include <OGLML/Sprite.h>

#include <OGLML/QuadRender.h>

#include <glew.h>

using namespace oglml;

Sprite::Sprite(Texture2D& texture, Shader& shader)
{
	m_textureID = texture.GetTextureID();
	m_shaderID = shader.GetProgramID();
}

void Sprite::Draw()
{
	static const std::string imageUniform = "uImage";
	static const std::string projectionUniform = "uProjection";
	static const std::string modelUniform = "uModel";
	static const std::string colorUniform = "uColor";
	static const unsigned int IMAGE_LAYOUT_POSITION = 0;

	Shader::Use(m_shaderID);
	Shader::SetMatrix4f(m_shaderID, projectionUniform, m_projection);
	Shader::SetInt(m_shaderID, imageUniform, IMAGE_LAYOUT_POSITION);
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(m_position, 0.0f));

	model = glm::translate(model, glm::vec3(0.5f * m_size.x, 0.5f * m_size.y, 0.0f));
	model = glm::rotate(model, glm::radians(m_rotate), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::translate(model, glm::vec3(-0.5f * m_size.x, -0.5f * m_size.y, 0.0f));

	model = glm::scale(model, glm::vec3(m_size, 1.0f));

	Shader::SetMatrix4f(m_shaderID, modelUniform, model);
	Shader::SetVector3f(m_shaderID, colorUniform, m_color);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_textureID);

	QuadRender::Get().Draw();
}

void Sprite::SetScreenSize(float width, float height)
{
	m_projection = glm::ortho(0.0f, width, height, 0.0f, -1.0f, 1.0f);
}

void Sprite::SetRotateAngle(float rotate)
{
	m_rotate = rotate;
}

void Sprite::SetColor(std::array<float, 3>& color)
{
	m_color = glm::vec3(color[0], color[1], color[2]);
}

void Sprite::SetPosition(std::array<float, 2>& position)
{
	m_position = glm::vec2(position[0], position[1]);
}

void Sprite::SetSize(std::array<float, 2>& size)
{
	m_size = glm::vec2(size[0], size[1]);
}

