#pragma once
#include "KScript.h"

namespace KEngine
{
	class Player;
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

		void SetPlayer(std::shared_ptr<GameObject> player) { mPlayer = player; }
		void SetDest(KMath::Vector2 dest) { mDest = dest; }

	private:
		void SitDown();
		void Move();
		void LayDown();

		void PlayAnimByDirection(eDirection dir);

		eState mState;
		eDirection mDirection;

		std::shared_ptr<Animator> mAnimator;
		float mTime;
		float mDeathTime;

		std::shared_ptr<GameObject> mPlayer;
		KMath::Vector2 mDest;
		float mRadian;
	};	
}


