#pragma once
#include "CommonInclude.h"
#include "KEntity.h"

namespace KEngine
{

	class GameObject;

	class Component : public Entity
	{
	public:
		Component();
		virtual ~Component();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render(HDC hdc);
		virtual void Release();

		void SetOwner(std::weak_ptr<GameObject> owner) { mOwner = owner; };
		std::weak_ptr<GameObject> GetOwner() { return mOwner; }
	private:
		std::weak_ptr<GameObject> mOwner;
	};
}
