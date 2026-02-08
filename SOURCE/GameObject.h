#pragma once
#include "CommonInclude.h"
#include "KEntity.h"

namespace KEngine
{
	class Component;

	// 언리얼에서는 Actor
	class GameObject : public Entity
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

		template<typename T>
		T* AddComponent();

		template<typename T>
		T* GetComponent();

		virtual void		Initialize();
		virtual void		Update();
		virtual void		LateUpdate();
		virtual void		Render();
		virtual void		Release();

		bool				IsActive() const						{ return mState == eState::Active; }
		bool				IsDead() const							{ return mState == eState::Dead; }

		eLayerType			GetLayerType() const					{ return mLayerType; }
		void				SetLayerType(eLayerType layerType)		{ mLayerType = layerType; }

		eState				GetActive() const						{ return mState; }
		void				SetActive(bool power)					{ mState = power ? eState::Active : eState::Paused; }
		void				Death()									{ mState = eState::Dead; }

	private :
		eState										mState;
		std::vector<std::unique_ptr<Component>>		mComponents;
		eLayerType									mLayerType;
	};

	template <typename T>
	T* GameObject::AddComponent()
	{
		std::unique_ptr<T> comp = std::make_unique<T>();
		comp->Initialize();
		comp->SetOwner(this);

		T* rawComp = comp.get(); 

		mComponents[(UINT)comp->GetType()] = std::move(comp);

		return rawComp;
	}

	template <typename T>
	T* GameObject::GetComponent()
	{
		for (auto& comp : mComponents)
		{
			T* target = dynamic_cast<T*>(comp.get());
			if (target != nullptr) return target;
		}
		return nullptr;
	}
}
