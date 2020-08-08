#pragma once

#include <string>

namespace oglml
{
	class Texture2D
	{
	public:
		Texture2D() = default;
		~Texture2D();

		bool loadFromFile(const std::string& path, bool usingAlpha = false);
		unsigned int GetTextureID();

		void operator=(Texture2D&);

	private:

		unsigned int m_textureID = -1;

		bool b_init = false;
	};
}