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

			GameObject::eState state = gameObject->GetActive();
			if (state == GameObject::eState::Paused || state == GameObject::eState::Dead) continue;

			gameObject->Update();
		}
	}

	void Layer::LateUpdate()
	{
		for (auto& gameObject : mGameObjects)
		{
			if (gameObject == nullptr) continue;

			GameObject::eState state = gameObject->GetActive();
			if (state == GameObject::eState::Paused || state == GameObject::eState::Dead) continue;

			gameObject->LateUpdate();
		}
	}

	void Layer::Render(HDC hdc)
	{
		for (auto& gameObject : mGameObjects)
		{
			if (gameObject == nullptr) continue;

			GameObject::eState state = gameObject->GetActive();
			if (state == GameObject::eState::Paused || state == GameObject::eState::Dead) continue;

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

	void Layer::Destroy()
	{
		for (auto iter = mGameObjects.begin() ; iter != mGameObjects.end() ; )
		{
			GameObject::eState active = (*iter)->GetActive();
			if (active == GameObject::eState::Dead)
			{
				iter = mGameObjects.erase(iter);
				continue;
			}
			iter++;
		}
	}

	void Layer::AddGameObject(const std::shared_ptr<GameObject> gameObject)
	{
		if (gameObject) mGameObjects.push_back(gameObject);
	}
}
