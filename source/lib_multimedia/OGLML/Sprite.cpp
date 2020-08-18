#include <OGLML/Sprite.h>

using namespace oglml;

Sprite::Sprite()
{

}

void Sprite::SetTexture(Texture2D& texture)
{
	m_textureID = texture.GetTextureID();
}

void Sprite::SetShader(Shader& shader)
{
	m_shaderID = shader.GetProgramID();
}

void Sprite::SetScreenSize(float width, float height)
{
	m_projection = glm::ortho(0.0f, width, height, 0.0f, -1.0f, 1.0f);
}

void Sprite::SetRotateAngle(float rotate)
{
	m_rotate = rotate;
}

void Sprite::SetColor(const std::array<float, 3>& color)
{
	m_color = glm::vec3(color[0], color[1], color[2]);
}

void Sprite::SetPosition(const std::array<float, 2>& position)
{
	m_position = glm::vec2(position[0], position[1]);
}

void Sprite::SetSize(const std::array<float, 2>& size)
{
	m_size = glm::vec2(size[0], size[1]);
}

float Sprite::GetRotateAngle() const
{
	return m_rotate;
}

const glm::vec3& Sprite::GetColor() const
{
	return m_color;
}

const glm::vec2& Sprite::GetPosition() const
{
	return m_position;
}

const glm::vec2& Sprite::GetSize() const
{
	return m_size;
}

const glm::mat4& Sprite::GetProj() const
{
	return m_projection;
}

unsigned int Sprite::GetTextureID() const
{
	return m_textureID;
}

unsigned int Sprite::GetShaderID() const
{
	return m_shaderID;
}

