#pragma once
#include "KScript.h"

namespace KEngine
{
	class Player;
	class Animator;

	class CameraScript : public Script
	{
	public :
		CameraScript();
		~CameraScript();

		void	Initialize() override;
		void	Update() override;
		void	LateUpdate() override;
		void	Render(HDC hdc) override;
		void	Release() override;

	private:
	};	
}