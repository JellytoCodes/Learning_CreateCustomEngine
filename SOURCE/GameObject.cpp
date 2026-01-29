#include "GameObject.h"
#include "KComponent.h"
#include "KTransform.h"

namespace KEngine
{
	GameObject::GameObject()
	{
		mComponents.resize((UINT)KEngine::eComponentType::End);
	}

	GameObject::~GameObject()
	{

	}

	void GameObject::Initialize()
	{
		for (auto& comp : mComponents)
		{
			if (comp == nullptr) continue;
			comp->Initialize();
		}
	}

	void GameObject::Update()
	{
		for (auto& comp : mComponents)
		{
			if (comp == nullptr) continue;
			comp->Update();
		}
	}

	void GameObject::LateUpdate()
	{
		for (auto& comp : mComponents)
		{
			if (comp == nullptr) continue;
			comp->LateUpdate();
		}
	}

	void GameObject::Render(HDC hdc)
	{
		for (auto& comp : mComponents)
		{
			if (comp == nullptr) continue;
			comp->Render(hdc);
		}
	}

	void GameObject::Release()
	{
		for (auto& comp : mComponents)
		{
			if (comp == nullptr) continue;
			comp->Release();
		}
	}
}
