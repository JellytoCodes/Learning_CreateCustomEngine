#pragma once
#include "CommonInclude.h"

namespace KEngine
{
	class Component;

	// 언리얼에서는 Actor
	class GameObject : public std::enable_shared_from_this<GameObject>
	{
	public :
		enum class eState
		{
			Active,
			Paused,
			Dead,
			End
		};
		GameObject();
		~GameObject();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render(HDC hdc);
		virtual void Release();

		template<typename T>
		std::shared_ptr<T> AddComponent();

		template<typename T>
		std::shared_ptr<T> GetComponent();

		eState GetActive() { return mState; }
		void SetActive(bool power)
		{
			if (power == true)	mState = eState::Active; 
			if (power == false) mState = eState::Paused;
		}
		void Death() { mState = eState::Dead; }

	private :
		eState mState;
		std::vector<std::shared_ptr<Component>> mComponents;
	};

	template <typename T>
	std::shared_ptr<T> GameObject::AddComponent()
	{
		std::shared_ptr<T> comp = std::make_shared<T>();
		comp->Initialize();
		comp->SetOwner(shared_from_this());

		mComponents[(UINT)comp->GetType()] = comp;

		return comp;
	}

	template <typename T>
	std::shared_ptr<T> GameObject::GetComponent()
	{
		std::shared_ptr<T> component = nullptr;
		for (auto& comp : mComponents)
		{
			component = std::dynamic_pointer_cast<T>(comp);
			if (component) break;
		}
		return component;
	}
}
