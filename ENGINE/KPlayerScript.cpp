#include "KPlayerScript.h"

#include "KInput.h"
#include "KTime.h"
#include "KTransform.h"
#include "GameObject.h"
#include "KAnimator.h"

namespace KEngine
{
	PlayerScript::PlayerScript()
		: mState(eState::SitDown)
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
		case eState::SitDown :
			SitDown();
			break;
		case eState::Walk :
			Move();
			break;
		case eState::Sleep :
			break;
		case eState::GiveWater :
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

	void PlayerScript::SitDown()
	{
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
			mState = eState::SitDown;
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
}

