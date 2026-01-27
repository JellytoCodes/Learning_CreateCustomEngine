#pragma once
#include "KEntity.h"
#include "CommonInclude.h"
#include "GameObject.h"

namespace KEngine
{
	class Layer : public Entity
	{
	public :
		Layer();
		~Layer();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render(HDC hdc);
		virtual void Release();

		void AddGameObject(const std::shared_ptr<GameObject> gameObject);

	private :
		eLayerType mType;
		std::vector<std::shared_ptr<GameObject>> mGameObjects;
	};
}

