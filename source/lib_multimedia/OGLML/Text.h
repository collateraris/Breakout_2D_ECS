#pragma once

#include <string>
#include <array>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

namespace oglml
{
	class Font;

	struct TextInfo
	{
		unsigned int shaderId = 0;
		int width = -1;
		int height = -1;
	};

	class Text
	{
		using Color = std::array<float, 3>;

	public:

		Text(const TextInfo&);

		~Text();

		void SetString(const std::string& str);

		void SetFont(Font& font);

		void SetCharacterSize(unsigned int size);

		void SetFillColor(const Color& color);

		void SetOffset(float x, float y, float scale);

		void Draw();

	private:

		Font* m_font = nullptr;
		std::string m_string = "";
		unsigned int m_characterSize = 0;
		glm::vec3 m_fillColor = {1.f, 1.f, 1.f};
		unsigned int m_shaderId = 0;
		glm::mat4 m_projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f);
		float m_x_offset = 0.f;
		float m_y_offset = 0.f;
		float m_scale_offset = 0.f;

	};
}