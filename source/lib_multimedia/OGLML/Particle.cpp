#include <OGLML/Particle.h>

#include <OGLML/Texture2D.h>
#include <OGLML/Shader.h>
#include <OGLML/QuadRender.h>

#include <glew.h>

#include <cassert>

using namespace oglml;

Particle::Particle()
{
	glGenBuffers(1, &m_colorsVBO);
	glGenBuffers(1, &m_offsetsVBO);
}

void Particle::SetNumber(std::size_t size)
{
	assert(size > 0);

	m_particleNumber = size;
}

void Particle::SetOrthoParams(float width, float height)
{
	m_projection = glm::ortho(0.0f, width, height, 0.0f, -1.0f, 1.0f);
}

void Particle::SetTexture(Texture2D& texture)
{
	m_textureID = texture.GetTextureID();
}

void Particle::SetShader(Shader& shader)
{
	m_shaderID = shader.GetProgramID();
}

void Particle::BufferColorsData(const std::vector<ColorsData>& colors)
{
	assert(colors.size() == m_particleNumber);

	glBindBuffer(GL_ARRAY_BUFFER, m_colorsVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(ColorsData) * m_particleNumber, colors.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Particle::BufferOffsetsData(const std::vector<OffsetsData>& offsets)
{
	assert(offsets.size() == m_particleNumber);

	glBindBuffer(GL_ARRAY_BUFFER, m_offsetsVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(OffsetsData) * m_particleNumber, offsets.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Particle::Draw()
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

void Particle::BindData()
{
	QuadRender::Get().BindVAO();

	//COLORS
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorsVBO);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glVertexAttribDivisor(2, 1);

	//OFFSETS
	glEnableVertexAttribArray(3);
	glBindBuffer(GL_ARRAY_BUFFER, m_colorsVBO);
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glVertexAttribDivisor(3, 1);

	glBindVertexArray(0);
}