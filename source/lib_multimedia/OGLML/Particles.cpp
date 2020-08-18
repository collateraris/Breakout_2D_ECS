#include <OGLML/Particles.h>

#include <OGLML/Texture2D.h>
#include <OGLML/Shader.h>
#include <OGLML/QuadRender.h>

#include <glew.h>

#include <cassert>

using namespace oglml;

Particles::Particles()
{
	glGenBuffers(1, &m_colorsVBO);
	glGenBuffers(1, &m_offsetsVBO);
}

void Particles::SetNumber(std::size_t size)
{
	assert(size > 0);

	m_particleNumber = size;
}

void Particles::SetOrthoParams(float width, float height)
{
	m_projection = glm::ortho(0.0f, width, height, 0.0f, -1.0f, 1.0f);
}

void Particles::SetTexture(Texture2D& texture)
{
	m_textureID = texture.GetTextureID();
}

void Particles::SetShader(Shader& shader)
{
	m_shaderID = shader.GetProgramID();
}

void Particles::BufferColorsData(const std::vector<ColorsData>& colors)
{
	assert(colors.size() == m_particleNumber);

	glBindBuffer(GL_ARRAY_BUFFER, m_colorsVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(ColorsData) * m_particleNumber, colors.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Particles::BufferOffsetsData(const std::vector<OffsetsData>& offsets)
{
	assert(offsets.size() == m_particleNumber);

	glBindBuffer(GL_ARRAY_BUFFER, m_offsetsVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(OffsetsData) * m_particleNumber, offsets.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Particles::Draw()
{
	static const std::string imageUniform = "uSprite";
	static const std::string projectionUniform = "uProjection";
	static const unsigned int SPRITE_LAYOUT_POSITION = 0;

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	Shader::Use(m_shaderID);
	Shader::SetInt(m_shaderID, imageUniform, SPRITE_LAYOUT_POSITION);
	Shader::SetMatrix4f(m_shaderID, projectionUniform, m_projection);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_textureID);

	BindData();
	QuadRender::Get().DrawArraysInstanced(m_particleNumber);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void Particles::BindData()
{
	QuadRender::Get().BindVAO();

	//COLORS
	glBindBuffer(GL_ARRAY_BUFFER, m_colorsVBO);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glVertexAttribDivisor(2, 1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//OFFSETS
	glBindBuffer(GL_ARRAY_BUFFER, m_offsetsVBO);
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glVertexAttribDivisor(3, 1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}