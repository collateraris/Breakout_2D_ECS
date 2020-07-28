#pragma once

#include <string>
#include <unordered_map>

namespace breakout
{
	template <class ResourceType>
	class ResourcesManager
	{
	public:

		ResourcesManager();
		~ResourcesManager();

		bool Load(int resourceId, const std::string& path);

		bool Unload(int resourceId);

		bool GetResource(int resourceId, ResourceType& resource);

	protected:

		virtual bool getFromFile(const std::string& path, ResourceType& resource) = 0;

	private:

		std::unordered_map<int, ResourceType> m_resources;
	};

	template <class ResourceType>
	ResourcesManager<ResourceType>::ResourcesManager()
	{

	}

	template <class ResourceType>
	ResourcesManager<ResourceType>::~ResourcesManager()
	{

	}

	template <class ResourceType>
	bool ResourcesManager<ResourceType>::Load(int resourceId, const std::string& path)
	{
		if (m_resources.find(resourceId) != m_resources.end())
			return true;

		ResourceType resource;
		if (!getFromFile(path, resource))
			return false;

		m_resources[resourceId] = resource;
		return true;
	}

	template <class ResourceType>
	bool ResourcesManager<ResourceType>::Unload(int resourceId)
	{
		auto found = m_resources.find(resourceId);
		if (found == m_resources.end())
			return false;

		m_resources.erase(found);
		return true;
	}

	template <class ResourceType>
	bool ResourcesManager<ResourceType>::GetResource(int resourceId, ResourceType& resource)
	{
		auto found = m_resources.find(resourceId);
		if (found == m_resources.end())
		{
			return false;
		}

		resource = found->second;
		return true;
	}
}