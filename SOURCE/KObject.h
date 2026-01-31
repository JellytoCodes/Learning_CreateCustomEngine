#pragma once
#include "CommonInclude.h"

#include "KComponent.h"
#include "GameObject.h"
#include "KLayer.h"
#include "KSceneManager.h"
#include "KScene.h"
#include "KTransform.h"

namespace KObject
{
	template<typename T>
	static std::shared_ptr<T> Instantiate(KEngine::eLayerType type)
	{
		std::shared_ptr<T> gameObject = std::make_shared<T>();
		std::weak_ptr<KEngine::Scene> activeScene = KEngine::SceneManager::GetActiveScene();
		std::weak_ptr<KEngine::Layer> layer = activeScene.lock()->GetLayer(type);

		std::weak_ptr<KEngine::Transform> tr = gameObject->AddComponent<KEngine::Transform>();

		layer.lock()->AddGameObject(gameObject);

		return gameObject;
	}

	template<typename T>
	static std::shared_ptr<T> Instantiate(KEngine::eLayerType type, KMath::Vector2 position)
	{
		std::shared_ptr<T> gameObject = std::make_shared<T>();
		std::weak_ptr<KEngine::Scene> activeScene = KEngine::SceneManager::GetActiveScene();
		std::weak_ptr<KEngine::Layer> layer = activeScene.lock()->GetLayer(type);

		std::weak_ptr<KEngine::Transform> tr = gameObject->AddComponent<KEngine::Transform>();
		tr.lock()->SetPosition(position);

		layer.lock()->AddGameObject(gameObject);

		return gameObject;
	}

	static void Destroy(std::shared_ptr<KEngine::GameObject> obj)
	{
		obj->Death();
	}
}
