#pragma once
#include "CommonInclude.h"

#include "GameObject.h"
#include "KLayer.h"
#include "KSceneManager.h"
#include "KScene.h"
#include "KTransform.h"

namespace KObject
{
	template<typename T>
	static T* Instantiate(KEngine::eLayerType type)
	{
		std::unique_ptr<T> gameObject = std::make_unique<T>();
		gameObject->SetLayerType(type);
		KEngine::Scene* activeScene = KEngine::SceneManager::GetActiveScene();
		KEngine::Layer* layer = activeScene->GetLayer(type);

		gameObject->AddComponent<KEngine::Transform>();

		T* rawObject = gameObject.get();

		layer->AddGameObject(std::move(gameObject));

		return rawObject;
	}

	template<typename T>
	static T* Instantiate(KEngine::eLayerType type, KMath::Vector2 position)
	{
		std::unique_ptr<T> gameObject = std::make_unique<T>();
		gameObject->SetLayerType(type);
		KEngine::Scene* activeScene = KEngine::SceneManager::GetActiveScene();
		KEngine::Layer* layer = activeScene->GetLayer(type);

		KEngine::Transform* tr = gameObject->AddComponent<KEngine::Transform>();
		tr->SetPosition(position);

		T* rawObject = gameObject.get();

		layer->AddGameObject(std::move(gameObject));

		return rawObject;
	}

	static void Destroy(KEngine::GameObject* obj)
	{
		obj->Death();
	}

	static void DontDestroyOnLoad(KEngine::GameObject* obj)
	{
		if (obj == nullptr) return;

	    KEngine::Scene* activeScene = KEngine::SceneManager::GetActiveScene();
	    std::unique_ptr<KEngine::GameObject> movedObj = activeScene->RemoveGameObject(obj);

	    if (movedObj != nullptr)
	    {
	        KEngine::Scene* dontDestroyOnLoad = KEngine::SceneManager::GetDontDestroyOnLoad();
	        dontDestroyOnLoad->AddGameObject(std::move(movedObj), obj->GetLayerType());
	    }
	}
}
