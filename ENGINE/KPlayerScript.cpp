#include "KPlayerScript.h"

#include "KInput.h"
#include "KTime.h"
#include "KTransform.h"
#include "GameObject.h"
#include "KAnimator.h"
#include "KCat.h"
#include "KCatScript.h"
#include "KObject.h"
#include "KResources.h"

namespace KEngine
{
	PlayerScript::PlayerScript()
		: mState(eState::Idle)
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
		if (mAnimator == nullptr) mAnimator = GetOwner().lock()->GetComponent<Animator>();
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

	void PlayerScript::Render(HDC hdc)
	{
		
	}

	void PlayerScript::Release()
	{
		
	}

	void PlayerScript::AttackEffect()
	{
		// Cat
		{
			auto cat = KObject::Instantiate<Cat>(KEngine::eLayerType::Animal);
			cat->AddComponent<CatScript>();

			auto texture = Resources::Find<KEngine::Texture>(L"Cat");
			auto animator = cat->AddComponent<Animator>();

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

			cat->GetComponent<Transform>()->SetPosition(KMath::Vector2(200.f, 200.f));
			cat->GetComponent<Transform>()->SetScale(KMath::Vector2(2.f, 2.f));
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

		std::shared_ptr<Transform> tr = GetOwner().lock()->GetComponent<Transform>();
		KMath::Vector2 pos = tr->GetPosition();

		if (Input::GetKeyPressed(eKeyCode::Right))
		{
			pos.x += 100.f * Time::DeltaTime();
			mAnimator->PlayAnimation(L"RightWalk");
		}
		if (Input::GetKeyPressed(eKeyCode::Left))	
		{
			pos.x -= 100.f * Time::DeltaTime();
			mAnimator->PlayAnimation(L"LeftWalk");
		}
		if (Input::GetKeyPressed(eKeyCode::Up))
		{
			pos.y -= 100.f * Time::DeltaTime();
			mAnimator->PlayAnimation(L"UpWalk");
		}
		if (Input::GetKeyPressed(eKeyCode::Down))	
		{
			pos.y += 100.f * Time::DeltaTime();
			mAnimator->PlayAnimation(L"DownWalk");
		}

		tr->SetPosition(pos);
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

