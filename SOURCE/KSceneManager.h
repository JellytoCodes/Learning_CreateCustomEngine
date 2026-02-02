#pragma once
#include "CommonInclude.h"
#include "KScene.h"

namespace KEngine
{
	class SceneManager
	{
	public :
		template<typename T>
		static void CreateScene(const std::wstring& name);

		static Scene* LoadScene(const std::wstring& name);
		static Scene* GetActiveScene() { return mActiveScene; }

		static void Initialize();
		static void Update();
		static void LateUpdate();
		static void Render(HDC hdc);
		static void Release();
		static void Destroy();

	private :
		static std::map<const std::wstring, std::unique_ptr<Scene>> mScene;

		// 관찰자(Observer) 역할만 수행하므로 소유권이 없는 Raw Pointer를 사용한다.
		static Scene* mActiveScene;
	};

	template <typename T>
	void SceneManager::CreateScene(const std::wstring& name)
	{
		std::unique_ptr<T> scene = std::make_unique<T>();
		scene->SetName(name);
		mActiveScene = scene.get();
		scene->Initialize();

		mScene.insert(std::make_pair(name, std::move(scene)));
	}
}