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

		void AddGameObject(std::unique_ptr<GameObject> gameObject,const eLayerType type);

		Layer* GetLayer(const eLayerType type) { return mLayers[(UINT)type].get(); }

	private :
		std::vector<std::unique_ptr<Layer>> mLayers;
	};	
}


