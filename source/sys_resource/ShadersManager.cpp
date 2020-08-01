#include <ShadersManager.h>

using namespace breakout;

ShadersManager::ShadersManager()
	: ResourcesManager<oglml::Shader>()
{

};

ShadersManager::~ShadersManager()
{

};

ShadersManager& ShadersManager::Get()
{
	static ShadersManager shadersManager;
	return shadersManager;
};

bool ShadersManager::getFromFile(const std::string& path, oglml::Shader& resource)
{
	static const std::string VS = ".vs";
	static const std::string FS = ".fs";

	std::string vertexCode = path + VS;
	std::string fragmentCode = path + FS;

	return resource.loadFromFile(vertexCode, fragmentCode);
};
