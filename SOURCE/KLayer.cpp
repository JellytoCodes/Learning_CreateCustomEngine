#include "KLayer.h"

namespace KEngine
{
	Layer::Layer()
	{

	}

	Layer::~Layer()
	{

	}

	void Layer::Initialize()
	{
		for (auto& gameObject : mGameObjects)
		{
			if (gameObject == nullptr) continue;
			gameObject->Initialize();
		}
	}

	void Layer::Update()
	{
		for (auto& gameObject : mGameObjects)
		{
			if (gameObject == nullptr) continue;
			gameObject->Update();
		}
	}

	void Layer::LateUpdate()
	{
		for (auto& gameObject : mGameObjects)
		{
			if (gameObject == nullptr) continue;
			gameObject->LateUpdate();
		}
	}

	void Layer::Render(HDC hdc)
	{
		for (auto& gameObject : mGameObjects)
		{
			if (gameObject == nullptr) continue;
			gameObject->Render(hdc);
		}
	}

	void Layer::Release()
	{
		for (auto& gameObject : mGameObjects)
		{
			if (gameObject == nullptr) continue;
			gameObject->Release();
		}
	}

	void Layer::AddGameObject(const std::shared_ptr<GameObject> gameObject)
	{
		if (gameObject) mGameObjects.push_back(gameObject);
	}
}
