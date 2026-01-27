#pragma once
#include "KEntity.h"

namespace KEngine
{
	class GameObject;

	class Scene : public Entity
	{
	public :
		Scene();
		virtual ~Scene();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render(HDC hdc);
		virtual void Release();
		void AddGameObject(const std::shared_ptr<GameObject> gameObject);

	private :
		std::vector<std::shared_ptr<GameObject>> mGameObjects;
	};	
}


