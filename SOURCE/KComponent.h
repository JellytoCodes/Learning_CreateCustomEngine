#pragma once
#include "CommonInclude.h"
#include "KEntity.h"

namespace KEngine
{

	class GameObject;

	class Component : public Entity
	{
	public:
		Component(KEngine::eComponentType type);
		virtual ~Component();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render(HDC hdc);
		virtual void Release();

		void SetOwner(GameObject* owner) { mOwner = owner; };
		GameObject* GetOwner() { return mOwner; }
		KEngine::eComponentType GetType() { return mComponentType; }

	private:
		GameObject* mOwner;
		KEngine::eComponentType mComponentType;
	};
}