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
	m_projection = glm::ortho(0.0f, w, h, 0.0f, -1.0f, 1.0f);

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
	assert(!m_font);
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

void Text::Draw()
{
	assert(!m_font);
	assert(!m_characterSize);

	glActiveTexture(GL_TEXTURE0);
	DynamicQuadRender::Get().BindVAO();


}

