#pragma once
#include "../SOURCE/KScene.h"

namespace KEngine
{
	class Player;

	class ToolScene : public Scene
	{
	public :
		ToolScene();
		~ToolScene();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

		void OnEnter() override;
		void OnExit() override;
	};	
}
