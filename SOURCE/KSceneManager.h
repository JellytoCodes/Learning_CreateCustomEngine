#pragma once
#include "CommonInclude.h"
#include "KScene.h"

namespace KEngine
{
	class SceneManager
	{
	public :
		template<typename T>
		static Scene*	CreateScene(const std::wstring& name);

		static Scene*	LoadScene(const std::wstring& name);
		static Scene*	GetActiveScene()							{ return mActiveScene; }
		static Scene*	GetDontDestroyOnLoad()						{ return mDontDestroyOnLoad; }

		static void		Initialize();
		static void		Update();
		static void		LateUpdate();
		static void		Render(HDC hdc);
		static void		Release();
		static void		Destroy();

	private :
		static std::map<const std::wstring, std::unique_ptr<Scene>>		mScene;

		// 관찰자(Observer) 역할만 수행하므로 소유권이 없는 Raw Pointer를 사용한다.
		static Scene*													mActiveScene;
		static Scene*													mDontDestroyOnLoad;
	};

	template <typename T>
	Scene* SceneManager::CreateScene(const std::wstring& name)
	{
		std::unique_ptr<T> scene = std::make_unique<T>();
		scene->SetName(name);
		mActiveScene = scene.get();
		scene->Initialize();

		Scene* rawScene = scene.get();

		mScene.insert(std::make_pair(name, std::move(scene)));

		return rawScene;
	}
}