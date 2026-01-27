#include "KScene.h"

#include <memory>

#include "GameObject.h"
#include "algorithm"

namespace KEngine
{
	Scene::Scene()
	{
		mLayers.resize((UINT)eLayerType::Max);
		for (auto& layer : mLayers)
		{
			layer = std::make_shared<Layer>();
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

	void Scene::OnEnter()
	{

	}

	void Scene::OnExit()
	{

	}

	void Scene::AddGameObject(const std::shared_ptr<GameObject> gameObject, const eLayerType type)
	{
		mLayers[(UINT)type]->AddGameObject(gameObject);
	}
}


