#pragma once
#include "KEntity.h"
#include "KLayer.h"

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
		virtual void Destroy();

		virtual void OnEnter();
		virtual void OnExit();

		void AddGameObject(const std::shared_ptr<GameObject> gameObject, const eLayerType type);

		std::shared_ptr<Layer> GetLayer(const eLayerType type) { return mLayers[(UINT)type]; }

	private :
		std::vector<std::shared_ptr<Layer>> mLayers;
	};	
}


