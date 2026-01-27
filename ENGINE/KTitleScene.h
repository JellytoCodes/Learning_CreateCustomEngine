#pragma once
#include "../SOURCE/KScene.h"

namespace KEngine
{
	class TitleScene : public Scene
	{
	public :
		TitleScene();
		~TitleScene();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

	private :
	};
}


