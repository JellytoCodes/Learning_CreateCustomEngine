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
		: mState(eState::Idle), mAnimator(nullptr), mPixelMap(nullptr)
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

		Transform* tr = GetOwner()->GetComponent<Transform>();
		KMath::Vector2 pos = tr->GetPosition();
		COLORREF color = mPixelMap->GetPixel(pos.x, pos.y + 50);

		RigidBody* playerRb = GetOwner()->GetComponent<RigidBody>();
		if (color == RGB(255, 0, 0))
		{
			playerRb->SetGround(true);

			pos.y -= 1;
			tr->SetPosition(pos);
		}
		else
		{
			playerRb->SetGround(false);
		}
	}

	void PlayerScript::LateUpdate()
	{
		
	}

	void PlayerScript::Render(HDC hdc)
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
		// Cat
		{
			Cat* cat = KObject::Instantiate<Cat>(KEngine::eLayerType::Animal);
			CatScript* catSrc = cat->AddComponent<CatScript>();

			catSrc->SetPlayer(GetOwner());

			Texture* texture = Resources::Find<KEngine::Texture>(L"Cat");
			Animator* animator = cat->AddComponent<Animator>();

			// Create Animation By Cat
			animator->CreateAnimation(L"DownWalk", texture, 
			KMath::Vector2(0.f, 0.f), KMath::Vector2(32.f, 32.f), KMath::Vector2::Zero, 4, 0.2f);
			animator->CreateAnimation(L"RightWalk", texture, 
			KMath::Vector2(0.f, 32.f), KMath::Vector2(32.f, 32.f), KMath::Vector2::Zero, 4, 0.2f);
			animator->CreateAnimation(L"UpWalk", texture, 
			KMath::Vector2(0.f, 64.f), KMath::Vector2(32.f, 32.f), KMath::Vector2::Zero, 4, 0.2f);
			animator->CreateAnimation(L"LeftWalk", texture, 
			KMath::Vector2(0.f, 96.f), KMath::Vector2(32.f, 32.f), KMath::Vector2::Zero, 4, 0.2f);
			animator->CreateAnimation(L"SitDown", texture, 
			KMath::Vector2(0.f, 128.f), KMath::Vector2(32.f, 32.f), KMath::Vector2::Zero, 4, 0.2f);
			animator->CreateAnimation(L"Grooming", texture, 
			KMath::Vector2(0.f, 160.f), KMath::Vector2(32.f, 32.f), KMath::Vector2::Zero, 4, 0.2f);
			animator->CreateAnimation(L"LayDown", texture, 
			KMath::Vector2(0.f, 192.f), KMath::Vector2(32.f, 32.f), KMath::Vector2::Zero, 4, 0.2f);

			animator->PlayAnimation(L"SitDown", false);

			Transform* tr = GetOwner()->GetComponent<Transform>();

			cat->GetComponent<Transform>()->SetPosition(tr->GetPosition());
			cat->GetComponent<Transform>()->SetScale(KMath::Vector2(2.f, 2.f));

			KMath::Vector2 mousePosition = Input::GetMousePosition();
			catSrc->SetDest(mousePosition);
		}
	}

	void PlayerScript::Idle()
	{
		if (Input::GetKeyPressed(eKeyCode::LButton))
		{
			mState = eState::GiveWater;
			mAnimator->PlayAnimation(L"GiveWater", false);

			KMath::Vector2 Pos = Input::GetMousePosition();
		}

		if (Input::GetKeyPressed(eKeyCode::Right) 
		|| Input::GetKeyPressed(eKeyCode::Left)
		|| Input::GetKeyPressed(eKeyCode::Up) 
		|| Input::GetKeyPressed(eKeyCode::Down))	mState = eState::Walk;

		if (Input::GetKeyDown(eKeyCode::I))
		{
			UIManager::Push(eUIType::HpBar);
			//UIManager::Push(eUIType::Button);

		}

		if (Input::GetKeyDown(eKeyCode::O))
		{
			UIManager::Pop(eUIType::HpBar);

		}
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

