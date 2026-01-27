#include "KScene.h"
#include "GameObject.h"

namespace KEngine
{
	Scene::Scene()
	{

	}

	Scene::~Scene()
	{

	}

	void Scene::Initialize()
	{

	}

	void Scene::Update()
	{
		for (auto& gameObject : mGameObjects)
		{
			gameObject->Update();
		}
	}

	void Scene::LateUpdate()
	{
		for (auto& gameObject : mGameObjects)
		{
			gameObject->LateUpdate();
		}
	}

	void Scene::Render(HDC hdc)
	{
		for (auto& gameObject : mGameObjects)
		{
			gameObject->Render(hdc);
		}
	}

	void Scene::Release()
	{
		for (auto& gameObject : mGameObjects)
		{
			gameObject->Release();
		}
	}

	void Scene::AddGameObject(const std::shared_ptr<GameObject> gameObject)
	{
		mGameObjects.push_back(gameObject);
	}
}


