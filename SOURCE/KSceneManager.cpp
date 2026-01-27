#include "KSceneManager.h"

namespace KEngine
{
	std::map<const std::wstring, std::shared_ptr<KEngine::Scene>> SceneManager::mScene = { };
	std::shared_ptr<KEngine::Scene> KEngine::SceneManager::mActiveScene = nullptr;

	std::shared_ptr<Scene> SceneManager::LoadScene(const std::wstring& name)
	{
		std::map<std::wstring, std::shared_ptr<Scene>>::iterator It = mScene.find(name);

		if (It == mScene.end()) return nullptr;

		mActiveScene = It->second;

		return It->second;
	}

	void SceneManager::Initialize()
	{
		
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
		mActiveScene->Release();
	}
}
