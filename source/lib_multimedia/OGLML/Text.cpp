#include <OGLML/Text.h>

#include <OGLML/Font.h>
#include <OGLML/Shader.h>
#include <OGLML/DynamicQuadRender.h>

#include <glew.h>

#include <cassert>

using namespace oglml;

Text::Text(const TextInfo& info)
{
	assert(info.width != -1);
	assert(info.height != -1);

	m_shaderId = info.shaderId;

	float w = static_cast<float>(info.width);
	float h = static_cast<float>(info.height);
	m_projection = glm::ortho(0.0f, w, h, 0.0f);

	static const std::string uniformProjStr = "uProjection";
	static const std::string uniformTextTextureStr = "uText";

	Shader::Use(m_shaderId);
	Shader::SetMatrix4f(m_shaderId, uniformProjStr.c_str(), m_projection);
	Shader::SetInt(m_shaderId, uniformTextTextureStr.c_str(), 0);
}

Text::~Text()
{

}

void Text::SetString(const std::string& str)
{
	m_string = str;
}

void Text::SetFont(Font& font)
{
	m_font = &font;
}

void Text::SetCharacterSize(unsigned int size)
{
	assert(m_font);
	m_characterSize = size;
	m_font->SetCurrentSize(m_characterSize);
}

void Text::SetFillColor(const Color& color)
{
	m_fillColor = glm::vec3(color[0], color[1], color[2]);

	static const std::string uniformTextColor = "uTextColor";
	Shader::Use(m_shaderId);
	Shader::SetVector3f(m_shaderId, uniformTextColor.c_str(), m_fillColor);
}

void Text::SetOffset(float x, float y, float scale)
{
	m_x_offset = x;
	m_y_offset = y;
	m_scale_offset = scale;
}

void Text::Draw()
{
	assert(m_font);
	assert(m_characterSize);

	Shader::Use(m_shaderId);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glActiveTexture(GL_TEXTURE0);
	DynamicQuadRender::Get().BindVAO();

	static const char H_char = 'H';
	int bearing_y_pos_h_char = m_font->GetGlyph(H_char, m_characterSize).Bearing[1];

	float x = m_x_offset;
	float y = m_y_offset;
	float scale = m_scale_offset;

	for(auto& c: m_string)
	{
		const Glyph& glyph = m_font->GetGlyph(c, m_characterSize);

		float xpos = x + glyph.Bearing[0] * scale;
		float ypos = y + (bearing_y_pos_h_char - glyph.Bearing[1]) * scale;

		float w = glyph.Size[0] * scale;
		float h = glyph.Size[1] * scale;

		float vertices[20] = {
			xpos,     ypos + h, 0.0f,   0.0f, 1.0f ,
			xpos,     ypos, 0.0f,       0.0f, 0.0f ,
			xpos + w, ypos + h, 0.0f,   1.0f, 1.0f ,
			xpos + w, ypos,  0.0f,      1.0f, 0.0f
		};

		// render glyph texture over quad
		glBindTexture(GL_TEXTURE_2D, glyph.TextureID);
		// update content of VBO memory
		DynamicQuadRender::Get().BindBuffer();
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		DynamicQuadRender::Get().Draw();

		// now advance cursors for next glyph (note that advance is number of 1/64 pixels)
		x += (glyph.Advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64)

	}

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

