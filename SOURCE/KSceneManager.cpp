#include "KSceneManager.h"

#include "KDontDestroyOnLoad.h"

namespace KEngine
{
	std::map<const std::wstring, std::unique_ptr<Scene>> SceneManager::mScene = {};
	Scene* SceneManager::mActiveScene =nullptr;
	Scene* SceneManager::mDontDestroyOnLoad = nullptr;

	Scene* SceneManager::LoadScene(const std::wstring& name)
	{
		if (mActiveScene) mActiveScene->OnExit();
		
		auto It = mScene.find(name);

		if (It == mScene.end()) return nullptr;

		mActiveScene = It->second.get();
		mActiveScene->OnEnter();

		return mActiveScene;
	}

	std::vector<GameObject*> SceneManager::GetGameObjects(eLayerType layer)
	{
		std::vector<GameObject*> gameObjects;
	    
	    const auto& activeObjects = mActiveScene->GetLayer(layer)->GetGameObjects();
	    const auto& dontDestroyOnLoadObjects = mDontDestroyOnLoad->GetLayer(layer)->GetGameObjects();

	    gameObjects.reserve(activeObjects.size() + dontDestroyOnLoadObjects.size());

	    for (const auto& obj : activeObjects)
	    {
	        gameObjects.push_back(obj.get());
	    }

	    for (const auto& obj : dontDestroyOnLoadObjects)
	    {
	        gameObjects.push_back(obj.get());
	    }

	    return gameObjects;
	}

	void SceneManager::Initialize()
	{
		mDontDestroyOnLoad = CreateScene<DontDestroyOnLoad>(L"DontDestroyOnLoad");
		mActiveScene->Initialize();
	}

	void SceneManager::Update()
	{
		mActiveScene->Update();
		mDontDestroyOnLoad->Update();
	}

	void SceneManager::LateUpdate()
	{
		mActiveScene->LateUpdate();
		mDontDestroyOnLoad->LateUpdate();
	}

	void SceneManager::Render(HDC hdc)
	{
		mActiveScene->Render(hdc);
		mDontDestroyOnLoad->Render(hdc);
	}

	void SceneManager::Release()
	{
		for (auto& pair : mScene)
		{
			pair.second->Release();
		}
		mDontDestroyOnLoad->Release();
	}

	void SceneManager::Destroy()
	{
		mActiveScene->Destroy();
		mDontDestroyOnLoad->Destroy();
	}
}
