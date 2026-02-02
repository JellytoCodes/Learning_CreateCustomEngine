#pragma once
#include "KResource.h"
#include "KTexture.h"

namespace KEngine
{
	class Resources
	{
	public :
		template<typename T>
		static T* Find(const std::wstring& key);

		template<typename T>
		static T* Load(const std::wstring& key, const std::wstring& path);

		static void Release()
		{
			mResources.clear();
		}

		static void Insert(const std::wstring& key, std::unique_ptr<Resource> resource)
		{
			if (key == L"" || resource == nullptr) return;

			mResources.insert(std::make_pair(key, std::move(resource)));
		}

	private :
		// 현재는 LoadResources에서 자원을 미리 생성하기 때문에 unique_ptr을 사용한다.
		// 만약 특정 객체에서 Texture를 Load하는 방식이라면 weak_ptr로 사용하고
		// 특정 객체에선 shared_ptr을 통해서 레퍼런스 카운팅이 올라가 메모리에서 해제되지 않도록 한다.
		static std::map<std::wstring, std::unique_ptr<Resource>> mResources;
	};

	template <typename T>
    T* Resources::Find(const std::wstring& key)
    {
        auto iter = mResources.find(key);
        if (iter == mResources.end()) return nullptr;

        return dynamic_cast<T*>(iter->second.get());
    }

    template <typename T>
    T* Resources::Load(const std::wstring& key, const std::wstring& path)
    {
        T* resource = Resources::Find<T>(key);
        if (resource != nullptr) return resource;

        std::unique_ptr<T> newRes = std::make_unique<T>();
		if (FAILED(newRes->Load(path))) 
        {
            assert(false);
            return nullptr;
        }
		
        newRes->SetName(key);
        newRes->SetPath(path);
        
        T* rawPtr = newRes.get();

        mResources.insert(std::make_pair(key, std::move(newRes)));

        return rawPtr;
    }
}


