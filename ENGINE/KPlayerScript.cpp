#include "KPlayerScript.h"

#include "KInput.h"
#include "KTime.h"
#include "KTransform.h"
#include "GameObject.h"
#include "KAnimator.h"
#include "KCat.h"
#include "KCatScript.h"
#include "KCollider.h"
#include "KObject.h"
#include "KResources.h"
#include "KRigidBody.h"
#include "KUIManager.h"

namespace KEngine
{
	PlayerScript::PlayerScript()
		: mState(eState::Idle), mAnimator(nullptr)
	{

	}

	PlayerScript::~PlayerScript()
	{

	}

	void PlayerScript::Initialize()
	{
		
	}

	void PlayerScript::Update()
	{
		if (mAnimator == nullptr) mAnimator = GetOwner()->GetComponent<Animator>();
		switch (mState)
		{
		case eState::Idle :
			Idle();
			break;
		case eState::Walk :
			Move();
			break;
		case eState::Sleep :
			break;
		case eState::GiveWater :
			GiveWater();
			break;
		case eState::Attack :
			break;
		}
	}

	void PlayerScript::LateUpdate()
	{
		
	}

	void PlayerScript::Render()
	{
		
	}

	void PlayerScript::Release()
	{
		
	}

	void PlayerScript::OnCollisionEnter(Collider* other)
	{
		//GameObject* obj = other->GetOwner();
		//obj->GetComponent<Transform>()->SetPosition(KMath::Vector2(0,0));
	}

	void PlayerScript::OnCollisionStay(Collider* other)
	{

	}

	void PlayerScript::OnCollisionExit(Collider* other)
	{

	}

	void PlayerScript::AttackEffect()
	{

	}

	void PlayerScript::Idle()
	{

	}

	void PlayerScript::Move()
	{
		if (Input::GetKeyUp(eKeyCode::Right)
		|| Input::GetKeyUp(eKeyCode::Left)
		|| Input::GetKeyUp(eKeyCode::Up) 
		|| Input::GetKeyUp(eKeyCode::Down))
		{
			mState = eState::Idle;
			mAnimator->PlayAnimation(L"SitDown", false);
		}

		Transform* tr = GetOwner()->GetComponent<Transform>();
		KMath::Vector2 pos = tr->GetPosition();
		RigidBody* rb = GetOwner()->GetComponent<RigidBody>();

		if (Input::GetKeyPressed(eKeyCode::Right))
		{
			//pos.x += 100.f * Time::DeltaTime();
			rb->AddForce(KMath::Vector2(20.f, 0.f));
			mAnimator->PlayAnimation(L"RightWalk");
		}

		if (Input::GetKeyPressed(eKeyCode::Left))	
		{
			//pos.x -= 100.f * Time::DeltaTime();
			rb->AddForce(KMath::Vector2(-20.f, 0.f));
			mAnimator->PlayAnimation(L"LeftWalk");
		}

		if (Input::GetKeyPressed(eKeyCode::Up))
		{
			//pos.y -= 100.f * Time::DeltaTime();
			//rb->AddForce(KMath::Vector2(0.f, -20.f));
			mAnimator->PlayAnimation(L"UpWalk");

			KMath::Vector2 velocity = rb->GetVelocity();
			velocity.y = -500.f;
			rb->SetVelocity(velocity);

			rb->SetGround(false);
		}

		if (Input::GetKeyPressed(eKeyCode::Down))	
		{
			//pos.y += 100.f * Time::DeltaTime();
			rb->AddForce(KMath::Vector2(0.f, 20.f));
			mAnimator->PlayAnimation(L"DownWalk");
		}

		//tr->SetPosition(pos);
	}

	void PlayerScript::GiveWater()
	{
		if (mAnimator->IsComplete())
		{
			mState = eState::Idle;
			mAnimator->PlayAnimation(L"Idle", false);
		}
	}
}

