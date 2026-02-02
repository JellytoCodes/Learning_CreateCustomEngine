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
		// Dead 상태인 객체들을 한 번에 찾아서 메모리 해제 및 벡터 정리
		std::erase_if(mGameObjects, [](const std::unique_ptr<GameObject>& obj) 
		{
            return obj->GetActive() == GameObject::eState::Dead;
        });
	}

	void Layer::AddGameObject(std::unique_ptr<GameObject> gameObject)
	{
		if (gameObject) mGameObjects.push_back(std::move(gameObject));
	}
}
