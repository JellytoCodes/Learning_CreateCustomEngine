#include "KSceneManager.h"

namespace KEngine
{
	std::map<const std::wstring, std::unique_ptr<Scene>> SceneManager::mScene = {};
	Scene*SceneManager::mActiveScene =nullptr;

	Scene* SceneManager::LoadScene(const std::wstring& name)
	{
		if (mActiveScene) mActiveScene->OnExit();
		
		auto It = mScene.find(name);

		if (It == mScene.end()) return nullptr;

		mActiveScene = It->second.get();
		mActiveScene->OnEnter();

		return mActiveScene;
	}

	void SceneManager::Initialize()
	{
		mActiveScene->Initialize();
	}

	void SceneManager::Update()
	{
		mActiveScene->Update();
	}

	void SceneManager::LateUpdate()
	{
		mActiveScene->LateUpdate();
	}

	void SceneManager::Render(HDC hdc)
	{
		mActiveScene->Render(hdc);
	}

	void SceneManager::Release()
	{
		for (auto& pair : mScene)
		{
			pair.second->Release();
		}
	}

	void SceneManager::Destroy()
	{
		mActiveScene->Destroy();
	}
}
