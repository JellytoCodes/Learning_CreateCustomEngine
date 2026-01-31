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

		static std::shared_ptr<Scene> LoadScene(const std::wstring& name);
		static std::shared_ptr<Scene> GetActiveScene() { return mActiveScene; }

		static void Initialize();
		static void Update();
		static void LateUpdate();
		static void Render(HDC hdc);
		static void Release();
		static void Destroy();

	private :
		static std::map<const std::wstring, std::shared_ptr<Scene>> mScene;
		static std::shared_ptr<Scene> mActiveScene;
	};

	template <typename T>
	void SceneManager::CreateScene(const std::wstring& name)
	{
		std::shared_ptr<T> scene = std::make_shared<T>();
		scene->SetName(name);
		mActiveScene = scene;
		scene->Initialize();

		mScene.insert(std::make_pair(name, scene));
	}
}