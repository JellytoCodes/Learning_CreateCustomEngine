#include "GameObject.h"
#include "KComponent.h"
#include "KTransform.h"

namespace KEngine
{
	GameObject::GameObject()
	{
		
	}

	GameObject::~GameObject()
	{

	}

	void GameObject::Initialize()
	{
		for (auto& comp : mComponents)
		{
			comp->Initialize();
		}
	}

	void GameObject::Update()
	{
		for (auto& comp : mComponents)
		{
			comp->Update();
		}
	}

	void GameObject::LateUpdate()
	{
		for (auto& comp : mComponents)
		{
			comp->LateUpdate();
		}
	}

	void GameObject::Render(HDC hdc)
	{
		for (auto& comp : mComponents)
		{
			comp->Render(hdc);
		}
	}

	void GameObject::Release()
	{
		for (auto& comp : mComponents)
		{
			comp->Release();
		}
	}
}
