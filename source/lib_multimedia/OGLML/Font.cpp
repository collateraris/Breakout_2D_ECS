#include <OGLML/Font.h>

#include <OGLML/Texture2D.h>

#include <gtc/matrix_transform.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H

#include <glew.h>

#include <iostream>
#include <cassert>

using namespace oglml;

Font::Font()
{

}

Font::~Font()
{

}

bool Font::loadFromFile(const std::string& path)
{
	m_font = path;
	return true;
}

bool Font::SetCurrentSize(unsigned int characterSize)
{
    //check
    auto& foundIt = m_pages.find(characterSize);
    if (foundIt != m_pages.end())
        return false;


	const size_t FIRST_127C_ASCHII = 127;
	Page page;
    page.glyphs.reserve(FIRST_127C_ASCHII + 1);

    // initialize and load the FreeType library
    FT_Library ft;
    if (FT_Init_FreeType(&ft)) // all functions return a value different than 0 whenever an error occurred
    {
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
        assert(false);
    }
    // load font as face
    FT_Face face;
    if (FT_New_Face(ft, m_font.c_str(), 0, &face))
    {
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
        assert(false);
    }

    // set size to load glyphs as
    FT_Set_Pixel_Sizes(face, 0, characterSize);
    // disable byte-alignment restriction
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    Texture2DInfo texInfo;
    texInfo.format = GL_RED;
    texInfo.internalFormat = GL_RED;
    texInfo.type = GL_UNSIGNED_BYTE;
    texInfo.wrap_s = GL_CLAMP_TO_EDGE;
    texInfo.wrap_t = GL_CLAMP_TO_EDGE;
    texInfo.max_filter = GL_LINEAR;
    texInfo.min_filter = GL_LINEAR;

    Texture2D texGenerator;

    for (GLubyte c = 0; c <= FIRST_127C_ASCHII; c++)
    {
        // load character glyph 
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
            continue;
        }

        texInfo.width = face->glyph->bitmap.width;
        texInfo.height = face->glyph->bitmap.rows;
        texInfo.pixels = face->glyph->bitmap.buffer;

        texGenerator.Generate(texInfo);
        unsigned int texID = texGenerator.GetTextureID();

        Glyph glyph = { texID,
            {face->glyph->bitmap.width, face->glyph->bitmap.rows},
            {face->glyph->bitmap_left, face->glyph->bitmap_top},
            face->glyph->advance.x };

        page.glyphs.push_back(glyph);
    }

    m_pages[characterSize] = page;

    // destroy FreeType once we're finished
    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    return true;
}

const Glyph& Font::GetGlyph(unsigned int codePoint, unsigned int characterSize) const
{
    auto& foundPageIt = m_pages.find(characterSize);
    assert(foundPageIt != m_pages.end());

    const auto& page = foundPageIt->second;
    assert(codePoint < page.glyphs.size());

    return page.glyphs[static_cast<size_t>(codePoint)];
}