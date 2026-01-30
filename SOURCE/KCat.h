#pragma once
#include "GameObject.h"

namespace KEngine
{
	class Cat : public GameObject
	{
	public :
		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

	private :
	};	
}


