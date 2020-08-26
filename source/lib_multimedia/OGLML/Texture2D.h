#pragma once

#include <string>

namespace oglml
{
	struct Texture2DInfo
	{
		int width = -1;
		int height = -1;
		unsigned int format = 0;
		unsigned int internalFormat = 0;
		unsigned int type = 0;
		void* pixels = nullptr;
		int wrap_s = -1;
		int wrap_t = -1;
		int min_filter = -1;
		int max_filter = -1;
	};

	class Texture2D
	{
	public:
		Texture2D() = default;
		~Texture2D();

		bool loadFromFile(const std::string& path, bool usingAlpha = false);
		unsigned int GetTextureID();

		void operator=(Texture2D&);

		void Generate(Texture2DInfo& params);

	private:

		unsigned int m_textureID = -1;

		bool b_init = false;
	};
}