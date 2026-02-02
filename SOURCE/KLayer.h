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
		virtual void Destroy();

		void AddGameObject(std::unique_ptr<GameObject> gameObject);
		std::unique_ptr<GameObject> RemoveGameObject(GameObject* obj);
		void EraseGameObject(GameObject* obj);

		const std::vector<std::unique_ptr<GameObject>>& GetGameObjects() { return mGameObjects; }

	private :

		eLayerType mType;
		std::vector<std::unique_ptr<GameObject>> mGameObjects;
	};
}
