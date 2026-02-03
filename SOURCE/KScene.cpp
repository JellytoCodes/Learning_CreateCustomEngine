#include "KScene.h"

#include <memory>

#include "GameObject.h"
#include "algorithm"
#include "KCollisionManager.h"

namespace KEngine
{
	Scene::Scene()
	{
		mLayers.resize((UINT)eLayerType::Max);
		for (auto& layer : mLayers)
		{
			layer = std::make_unique<Layer>();
		}
	}

	Scene::~Scene()
	{

	}

	void Scene::Initialize()
	{
		for (auto& layer : mLayers)
		{
			if (layer == nullptr) continue;
			layer->Initialize();
		}
	}

	void Scene::Update()
	{
		for (auto& layer : mLayers)
		{
			if (layer == nullptr) continue;
			layer->Update();
		}
	}

	void Scene::LateUpdate()
	{
		for (auto& layer : mLayers)
		{
			if (layer == nullptr) continue;
			layer->LateUpdate();
		}
	}

	void Scene::Render(HDC hdc)
	{
		for (auto& layer : mLayers)
		{
			if (layer == nullptr) continue;
			layer->Render(hdc);
		}
	}

	void Scene::Release()
	{
		for (auto& layer : mLayers)
		{
			if (layer == nullptr) continue;
			layer->Release();
		}
	}

	void Scene::Destroy()
	{
		for (auto& layer : mLayers)
		{
			if (layer == nullptr) continue;
			layer->Destroy();
		}
	}

	void Scene::OnEnter()
	{

	}

	void Scene::OnExit()
	{
		CollisionManager::Clear();
	}

	void Scene::AddGameObject(std::unique_ptr<GameObject> gameObject, const eLayerType type)
	{
		mLayers[(UINT)type]->AddGameObject(std::move(gameObject));
	}

	std::unique_ptr<GameObject> Scene::RemoveGameObject(GameObject* obj)
	{
		eLayerType layerType = obj->GetLayerType();
	    return mLayers[(UINT)layerType]->RemoveGameObject(obj);
	}

	void Scene::EraseGameObject(GameObject* obj)
	{
		eLayerType layerType = obj->GetLayerType();
		mLayers[(UINT)layerType].get()->EraseGameObject(obj);
	}
}


