#pragma once
#include "KScript.h"

namespace KEngine
{
	class PlayerScript : public Script
	{
	public :
		PlayerScript();
		~PlayerScript();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;
		void Release() override;

	private:
	};	
}


