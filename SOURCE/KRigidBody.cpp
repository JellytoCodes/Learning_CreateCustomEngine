#include "KRigidBody.h"

#include "GameObject.h"
#include "KTime.h"
#include "KTransform.h"

namespace KEngine
{
	RigidBody::RigidBody()
		: Super(eComponentType::RigidBody),
		mbGround(false), mMass(1.f), mFriction(10.f),
		mForce(KMath::Vector2::Zero), mAcceleration(KMath::Vector2::Zero),
		mLimitVelocity(KMath::Vector2(200.f, 1000.f)), mVelocity(KMath::Vector2::Zero), mGravity(KMath::Vector2(0.f, 800.f))
	{

	}

	RigidBody::~RigidBody()
	{

	}

	void RigidBody::Initialize()
	{

	}

	void RigidBody::Update()
	{
		// f(힘) = m(질량) * a(가속도)

		// a = f / m
		mAcceleration = mForce / mMass;

		// 속도에 가속도를 더한다.
		mVelocity += mAcceleration * Time::DeltaTime();

		if (mbGround)
		{
			// 땅 위에 있을 때
			KMath::Vector2 gravity = mGravity;
			gravity.Normalize();

			float dot = mVelocity.Dot(gravity);
			mVelocity -= gravity * dot;
		}
		else
		{
			// 공중에 있을 때
			mVelocity += mGravity * Time::DeltaTime();
		}

		// 최대 속도 제한
		KMath::Vector2 gravity = mGravity;
		gravity.Normalize();
		float dot = mVelocity.Dot(gravity);
		gravity = gravity * dot;

		KMath::Vector2 sideVelocity = mVelocity - gravity;
		if (mLimitVelocity.y < gravity.Length())
		{
			gravity.Normalize();
			gravity *= mLimitVelocity.y;
		}

		if (mLimitVelocity.x < sideVelocity.Length())
		{
			sideVelocity.Normalize();
			sideVelocity *= mLimitVelocity.x;
		}
		mVelocity = gravity + sideVelocity;

		if (!(mVelocity == KMath::Vector2::Zero))
		{
			// 속도에 반대방향으로 마찰력 작용
			KMath::Vector2 friction = -mVelocity;
			friction.Normalize();
			friction = friction * (mFriction * mMass * Time::DeltaTime());

			// 마찰력으로 인한 속도 감소량이 현재 속도보다 큰 경우
			if (mVelocity.Length() <= friction.Length())	
			{
				mVelocity = KMath::Vector2::Zero; /*정지*/
			}
			else
			{
				mVelocity += friction;
			}
			
		}
		Transform* tr = GetOwner()->GetComponent<Transform>();
		KMath::Vector2 pos = tr->GetPosition();
		pos = pos + mVelocity * Time::DeltaTime();
		tr->SetPosition(pos);

		mForce = KMath::Vector2::One;
	}

	void RigidBody::LateUpdate()
	{
		
	}

	void RigidBody::Render()
	{
		
	}

	void RigidBody::Release()
	{
		
	}
}
