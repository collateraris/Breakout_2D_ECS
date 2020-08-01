#pragma once

#include <OGLML/Texture2D.h>
#include <OGLML/Shader.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#include <array>

namespace oglml
{
	class Sprite
	{
	public:
		Sprite();
		~Sprite() = default;

		void SetTexture(Texture2D& texture);
		void SetShader(Shader& shader);

		void Draw();

		void SetScreenSize(float width, float height);
		void SetRotateAngle(float rotate);
		void SetColor(const std::array<float, 3>& color);
		void SetPosition(const std::array<float, 2>& position);
		void SetSize(const std::array<float, 2>& size);

	private:

		unsigned int m_textureID = 0;
		unsigned int m_shaderID = 0;

		glm::mat4 m_projection = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f);
		glm::vec2 m_position = glm::vec2(0.);
		glm::vec2 m_size = glm::vec2(1.);
		glm::vec3 m_color = glm::vec3(0.);
		float m_rotate = 0.5f;
	};
}