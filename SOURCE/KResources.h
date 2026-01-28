#pragma once
#include "KResource.h"

namespace KEngine
{
	class Resources
	{
	public :
		template<typename T>
		static std::shared_ptr<T> Find(const std::wstring& key);

		template<typename T>
		static std::shared_ptr<T> Load(const std::wstring& key, const std::wstring& path);

	private :
		static std::map<std::wstring, std::shared_ptr<Resource>> mResources;
	};

	template <typename T>
	std::shared_ptr<T> Resources::Find(const std::wstring& key)
	{
		auto iter = mResources.find(key);
		return iter == mResources.end() ? nullptr : std::dynamic_pointer_cast<T>(iter->second);
	}

	template <typename T>
	std::shared_ptr<T> Resources::Load(const std::wstring& key, const std::wstring& path)
	{
		std::shared_ptr<T> resource = Resources::Find<T>(key);

		if (resource == nullptr)
		{
			resource = std::make_shared<T>();
			assert(SUCCEEDED(resource->Load(path)));
		}

		resource->SetName(key);
		resource->SetPath(path);
		mResources.insert(std::make_pair(key, resource));

		return resource;
	}
}


