#pragma once

#include <array>

namespace oglml
{
	struct Glyph
	{
		Glyph() = default;
		~Glyph() = default;

		unsigned int TextureID; // ID handle of the glyph texture
		std::array<int, 2>   Size;      // size of glyph
		std::array<int, 2>   Bearing;   // offset from baseline to left/top of glyph
		unsigned int Advance;   // horizontal offset to advance to next glyph
	};
}