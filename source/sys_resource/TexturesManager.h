#pragma once

#include <ResourcesManager.h>

#include <OGLML/Texture2D.h>

#include <string>
#include <iostream>

namespace breakout
{
	class TexturesManager : public ResourcesManager<oglml::Texture2D>
	{
	public:

		static TexturesManager& Get();

		bool Load(int resourceId, const std::string& path);

	protected:

		virtual bool getFromFile(const std::string& path, oglml::Texture2D& resource) override;

	private:

		TexturesManager();
		~TexturesManager();
		TexturesManager(TexturesManager&) = delete;
		TexturesManager(TexturesManager&&) = delete;
		void operator=(TexturesManager&) = delete;
		void operator=(TexturesManager&&) = delete;
	};
}