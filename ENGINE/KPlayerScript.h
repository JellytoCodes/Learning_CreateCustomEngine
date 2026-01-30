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
			SitDown,
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

	private:
		void SitDown();
		void Move();

		eState mState;
		std::shared_ptr<Animator> mAnimator;
	};	
}


