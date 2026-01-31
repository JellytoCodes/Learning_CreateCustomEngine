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

		static void Release()
		{
			for (auto& pair : mResources)
			{
				pair.second->Release();
			}
			mResources.clear();
		}

		static void Insert(const std::wstring& key, std::shared_ptr<Resource> resource)
		{
			if (key == L"") return;
			if (resource == nullptr) return;

			mResources.insert(std::make_pair(key, resource));
		}

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


