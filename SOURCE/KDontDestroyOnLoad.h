#pragma once
#include "KScene.h"

namespace KEngine
{
	class DontDestroyOnLoad : public Scene
	{
	public :
		DontDestroyOnLoad();
		~DontDestroyOnLoad();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;
		void Release() override;
		void Destroy() override;

		void OnEnter() override;
		void OnExit() override;
	};	
}


