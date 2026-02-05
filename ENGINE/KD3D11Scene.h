#pragma once
#include "../SOURCE/KScene.h"

namespace KEngine
{
	class Player;

	class D3D11Scene : public Scene
	{
	public :
		D3D11Scene();
		~D3D11Scene();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

		void OnEnter() override;
		void OnExit() override;

	private:
		void resourcesLoad(std::mutex& m);

		std::atomic<bool> mbLoadCompleted;
		std::thread* mResourcesLoad;
		std::mutex mMutex;
	};	
}
