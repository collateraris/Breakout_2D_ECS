#pragma once

#include <OGLML/Sprite.h>
#include <OGLML/QuadRender.h>

#include <glew.h>

namespace oglml
{
	template<size_t MAX_INSTANCE_RENDERING>
	class SpriteInstanced
	{
	public:
		SpriteInstanced();
		~SpriteInstanced() = default;

		void CollectSpriteData(const Sprite& sprite);
		void DrawInstanced();
		void ClearSpriteData();
		bool IsFull();
		void GenBuffers();

	private:

		void BufferData();
		void BindData();
		void InitData();

		unsigned int m_instances_number = 0;

		unsigned int m_textureID = 0;
		unsigned int m_shaderID = 0;

		unsigned int m_colorsVBO = 0;
		unsigned int m_projModelsVBO = 0;

		std::array<glm::vec3, MAX_INSTANCE_RENDERING> m_colors;
		std::array<glm::mat4, MAX_INSTANCE_RENDERING> m_projModels;
	};

	template<size_t MAX_INSTANCE_RENDERING>
	SpriteInstanced<MAX_INSTANCE_RENDERING>::SpriteInstanced()
	{
		InitData();
	}

	template<size_t MAX_INSTANCE_RENDERING>
	void SpriteInstanced<MAX_INSTANCE_RENDERING>::CollectSpriteData(const Sprite& sprite)
	{
		m_textureID = sprite.GetTextureID();
		m_shaderID = sprite.GetShaderID();

		m_colors[m_instances_number] = sprite.GetColor();

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(sprite.GetPosition(), 0.0f));

		model = glm::translate(model, glm::vec3(0.5f * sprite.GetSize().x, 0.5f * sprite.GetSize().y, 0.0f));
		model = glm::rotate(model, glm::radians(sprite.GetRotateAngle()), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::translate(model, glm::vec3(-0.5f * sprite.GetSize().x, -0.5f * sprite.GetSize().y, 0.0f));
		model = glm::scale(model, glm::vec3(sprite.GetSize(), 1.0f));

		glm::mat4 projectionModel = sprite.GetProj() * model;

		m_projModels[m_instances_number] = projectionModel;

		++m_instances_number;
	}

	template<size_t MAX_INSTANCE_RENDERING>
	void SpriteInstanced<MAX_INSTANCE_RENDERING>::DrawInstanced()
	{
		static const std::string imageUniform = "uImage";
		static const unsigned int IMAGE_LAYOUT_POSITION = 0;

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		Shader::Use(m_shaderID);
		Shader::SetInt(m_shaderID, imageUniform, IMAGE_LAYOUT_POSITION);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_textureID);

		BufferData();
		BindData();
		QuadRender::Get().DrawArraysInstanced(m_instances_number);

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	template<size_t MAX_INSTANCE_RENDERING>
	void SpriteInstanced<MAX_INSTANCE_RENDERING>::ClearSpriteData()
	{
		InitData();
	}

	template<size_t MAX_INSTANCE_RENDERING>
	void SpriteInstanced<MAX_INSTANCE_RENDERING>::GenBuffers()
	{
		glGenBuffers(1, &m_colorsVBO);
		glGenBuffers(1, &m_projModelsVBO);
	}

	template<size_t MAX_INSTANCE_RENDERING>
	void SpriteInstanced<MAX_INSTANCE_RENDERING>::BufferData()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_colorsVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * m_instances_number, m_colors.data(), GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindBuffer(GL_ARRAY_BUFFER, m_projModelsVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::mat4) * m_instances_number, m_projModels.data(), GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	template<size_t MAX_INSTANCE_RENDERING>
	void SpriteInstanced<MAX_INSTANCE_RENDERING>::BindData()
	{
		QuadRender::Get().BindVAO();
		//COLORS	
		glBindBuffer(GL_ARRAY_BUFFER, m_colorsVBO);
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
		glVertexAttribDivisor(2, 1);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		//PROJ-MODEL MATRIX
		GLsizei vec4Size = sizeof(glm::vec4);
		glBindBuffer(GL_ARRAY_BUFFER, m_projModelsVBO);
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)0);
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(vec4Size));
		glEnableVertexAttribArray(5);
		glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(2 * vec4Size));
		glEnableVertexAttribArray(6);
		glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(3 * vec4Size));

		glVertexAttribDivisor(3, 1);
		glVertexAttribDivisor(4, 1);
		glVertexAttribDivisor(5, 1);
		glVertexAttribDivisor(6, 1);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindVertexArray(0);
	}

	template<size_t MAX_INSTANCE_RENDERING>
	void SpriteInstanced<MAX_INSTANCE_RENDERING>::InitData()
	{
		m_instances_number = 0;
	}

	template<size_t MAX_INSTANCE_RENDERING>
	bool SpriteInstanced<MAX_INSTANCE_RENDERING>::IsFull()
	{
		return !(m_instances_number < MAX_INSTANCE_RENDERING);
	}
}