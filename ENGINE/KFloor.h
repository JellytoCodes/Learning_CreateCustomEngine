#pragma once
#include "GameObject.h"

namespace KEngine
{
	class Floor : public GameObject
	{
	public :
		Floor();
		~Floor();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

	private:
	};	
}


