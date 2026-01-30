#pragma once
#include "KScript.h"

namespace KEngine
{
	class Animator;

	class PlayerScript : public Script
	{
	public :
		enum class eState
		{
			Idle,
			Walk,
			Sleep,
			GiveWater,
			Attack,
		};

		PlayerScript();
		~PlayerScript();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;
		void Release() override;

		void AttackEffect();

	private:
		void Idle();
		void Move();
		void GiveWater();

		eState mState;
		std::shared_ptr<Animator> mAnimator;
	};	
}


