#include "KSceneManager.h"

namespace KEngine
{
	std::map<const std::wstring, std::shared_ptr<KEngine::Scene>> SceneManager::mScene = { };
	std::shared_ptr<KEngine::Scene> KEngine::SceneManager::mActiveScene = std::make_shared<Scene>();

	std::shared_ptr<Scene> SceneManager::LoadScene(const std::wstring& name)
	{
		if (mActiveScene) mActiveScene->OnExit();
		
		std::map<std::wstring, std::shared_ptr<Scene>>::iterator It = mScene.find(name);

		if (It == mScene.end()) return nullptr;

		mActiveScene = It->second;
		mActiveScene->OnEnter();

		return It->second;
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
