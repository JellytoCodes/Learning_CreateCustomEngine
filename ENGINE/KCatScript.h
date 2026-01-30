#pragma once
#include "KScript.h"

namespace KEngine
{
	class Animator;

	class CatScript : public Script
	{
	public :
		enum class eState
		{
			SitDown,
			Walk,
			Sleep,
			LayDown,
			Attack,
		};

		enum class eDirection
		{
			Left,
			Right,
			Down,
			Up,
			End
		};

		CatScript();
		~CatScript();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;
		void Release() override;

	private:
		void SitDown();
		void Move();
		void LayDown();

		void PlayAnimByDirection(eDirection dir);

		eState mState;
		eDirection mDirection;

		std::shared_ptr<Animator> mAnimator;
		float mTime;
	};	
}


