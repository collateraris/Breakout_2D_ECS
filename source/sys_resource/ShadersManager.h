#pragma once

#include <ResourcesManager.h>

#include <OGLML/Shader.h>

#include <string>

namespace breakout
{
	class ShadersManager : public ResourcesManager<oglml::Shader>
	{
	public:

		static ShadersManager& Get();

	protected:

		virtual bool getFromFile(const std::string& path, oglml::Shader& resource) override;

	private:

		ShadersManager();
		~ShadersManager();
		ShadersManager(ShadersManager&) = delete;
		ShadersManager(ShadersManager&&) = delete;
		void operator=(ShadersManager&) = delete;
		void operator=(ShadersManager&&) = delete;
	};
}