#pragma once

#include <OGLML/Glyph.h>

#include <vector>
#include <unordered_map>
#include <string>

namespace oglml
{
	class Text;

	class Font
	{
		using GlyphTable = std::vector<Glyph>;

		struct Page
		{
			GlyphTable glyphs = {};
		};

		using PageTable = std::unordered_map<unsigned int, Page>;

	public:

		Font();
		~Font();

		bool loadFromFile(const std::string& path);

		bool SetCurrentSize(unsigned int characterSize);

		const Glyph& GetGlyph(unsigned int codePoint, unsigned int characterSize) const;

	private:

		PageTable m_pages;
		std::string m_font;
	};
}