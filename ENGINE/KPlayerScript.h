#pragma once
#include "KScript.h"

namespace KEngine
{
	class Collider;
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

		void OnCollisionEnter(Collider* other) override;
		void OnCollisionStay(Collider* other) override;
		void OnCollisionExit(Collider* other) override;

		void AttackEffect();

	private:
		void Idle();
		void Move();
		void GiveWater();

		eState mState;
		std::shared_ptr<Animator> mAnimator;
	};	
}


