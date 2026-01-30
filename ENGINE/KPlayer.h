#pragma once
#include "GameObject.h"

namespace KEngine
{
	class Player : public GameObject
	{
	public :
		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

		void AttackEffect();

	private :
	};
}