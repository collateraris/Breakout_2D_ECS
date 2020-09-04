#pragma once

#include <ResourcesManager.h>

#include <OGLML/Font.h>

#include <string>

namespace breakout
{
	class FontsManager : public ResourcesManager<oglml::Font>
	{
	public:

		static FontsManager& Get();

	protected:

		virtual bool getFromFile(const std::string& path, oglml::Font& resource) override;

	private:

		FontsManager();
		~FontsManager();
		FontsManager(FontsManager&) = delete;
		FontsManager(FontsManager&&) = delete;
		void operator=(FontsManager&) = delete;
		void operator=(FontsManager&&) = delete;
	};
}