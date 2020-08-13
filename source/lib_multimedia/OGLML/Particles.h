#pragma once

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#include <array>
#include <vector>

namespace oglml
{
	class Texture2D;
	class Shader;

	class Particles
	{
		using ColorsData = std::array<float, 4>;
		using OffsetsData = std::array<float, 2>;

	public:

		Particles();
		~Particles() = default;

		void SetNumber(std::size_t size);
		void SetOrthoParams(float width, float height);

		void SetTexture(Texture2D& texture);
		void SetShader(Shader& shader);

		void BufferColorsData(const std::vector<ColorsData>& colors);
		void BufferOffsetsData(const std::vector<OffsetsData>& offsets);

		void Draw();

	protected:

		void BindData();

	private:

		unsigned int m_colorsVBO;
		unsigned int m_offsetsVBO;

		unsigned int m_textureID = 0;
		unsigned int m_shaderID = 0;

		std::size_t m_particleNumber = 500;

		glm::mat4 m_projection = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f);
	};
}