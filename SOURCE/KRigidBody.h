#pragma once
#include "KComponent.h"

namespace KEngine
{
	class RigidBody : public Component
	{
		using Super = Component;

	public :
		RigidBody();
		virtual ~RigidBody();

		void			Initialize() override;
		void			Update() override;
		void			LateUpdate() override;
		void			Render(HDC hdc) override;
		void			Release() override;

		void SetMass(float mass)					{ mMass = mass; }

		void AddForce(KMath::Vector2 force)			{ mForce = force; }

		void SetGround(bool ground)					{ mbGround = ground; }

		void SetVelocity(KMath::Vector2 velocity)	{ mVelocity = velocity; }
		KMath::Vector2 GetVelocity()				{ return mVelocity; }

	private :
		bool				mbGround;
		float				mMass;
		float				mFriction;

		KMath::Vector2		mForce;
		KMath::Vector2		mAcceleration;
		KMath::Vector2		mVelocity;
		KMath::Vector2		mLimitVelocity;
		KMath::Vector2		mGravity;
	};
}
