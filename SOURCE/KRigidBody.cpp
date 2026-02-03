#include "KRigidBody.h"

#include "GameObject.h"
#include "KTime.h"
#include "KTransform.h"

namespace KEngine
{
	RigidBody::RigidBody()
		: Super(eComponentType::RigidBody),
		mMass(1.f), mFriction(10.f), mForce(KMath::Vector2::Zero), mAcceleration(KMath::Vector2::Zero), mVelocity(KMath::Vector2::Zero), mGravity(KMath::Vector2::Zero)
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

		if (!(mVelocity == KMath::Vector2::Zero))
		{
			// 속도에 반대방향으로 마찰력 작용
			KMath::Vector2 friction = -mVelocity;
			friction = friction.Normalize() * mFriction * mMass * Time::DeltaTime();

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

		mForce.Clear();
	}

	void RigidBody::LateUpdate()
	{
		
	}

	void RigidBody::Render(HDC hdc)
	{
		
	}

	void RigidBody::Release()
	{
		
	}
}
