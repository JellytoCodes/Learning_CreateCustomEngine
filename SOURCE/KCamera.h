#pragma once
#include "KComponent.h"

namespace KEngine
{
	class Camera : public Component
	{
		using Super = Component;

	public :
		KMath::Vector2	CalculatePosition(KMath::Vector2 pos)		{ return pos - mDistance; }

		Camera();
		~Camera();

		void			Initialize() override;
		void			Update() override;
		void			LateUpdate() override;
		void			Render(HDC hdc) override;
		void			Release() override;

		void			SetTarget(GameObject* target)				{ mTarget = target; }

	private :
		KMath::Vector2		mDistance;
		KMath::Vector2		mResolution;
		KMath::Vector2		mLookPosition;

		GameObject*			mTarget;
	};	
}