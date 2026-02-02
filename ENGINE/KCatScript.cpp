#include "KCatScript.h"
#include "KInput.h"
#include "KTime.h"
#include "KTransform.h"
#include "GameObject.h"
#include "KAnimator.h"
#include "KObject.h"

namespace KEngine
{
	CatScript::CatScript()
		: mState(eState::SitDown),
		mAnimator(nullptr), mPlayer(nullptr),
		mTime(0.f), mDeathTime(0.f), mDest(KMath::Vector2::Zero), mRadian(0.f)
	{

	}

	CatScript::~CatScript()
	{

	}

	void CatScript::Initialize()
	{
		
	}

	void CatScript::Update()
	{
		mDeathTime += Time::DeltaTime();
		if (mDeathTime > 6.0f)
		{
			//KObject::Destroy(GetOwner());
		}
		GameObject* owner = GetOwner();
		if (!owner) return;

		if (mAnimator == nullptr) mAnimator = owner->GetComponent<Animator>();
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
		case eState::LayDown :
			LayDown();
			break;
		case eState::Attack :
			break;
		}
	}

	void CatScript::LateUpdate()
	{
		
	}

	void CatScript::Render(HDC hdc)
	{
		
	}

	void CatScript::Release()
	{
		
	}

	void CatScript::SitDown()
	{
		mTime += Time::DeltaTime();

		Transform* tr = GetOwner()->GetComponent<Transform>();
		KMath::Vector2 pos = tr->GetPosition();

		if (mPlayer)
		{
			// 마우스 위치 이동 (벡터의 뺄셈 활용)
			//Transform* playerTr = mPlayer->GetComponent<Transform>();
			//KMath::Vector2 dest = mDest - playerTr->GetPosition();
			//pos += dest.Normalize() * (50.f * Time::DeltaTime());

			// 삼각함수를 통한 이동
			//mRadian += 5.f * Time::DeltaTime();
			//pos += KMath::Vector2(1.f, 2.f * cosf(mRadian)) * (50.f * Time::DeltaTime());

			// 마우스 위치 뱡향으로 회전 후 마우스 위치 이동 (벡터의 내적 활용)
			//Transform* playerTr = mPlayer->GetComponent<Transform>();
			//KMath::Vector2 dest = mDest - playerTr->GetPosition();
			//dest.Normalize();
			//
			//float rotDegree = KMath::Vector2::Dot(dest, KMath::Vector2::Right); // cosTheta
			//rotDegree = KMath::ConvertToDegree(acosf(rotDegree));
			//
			//pos += dest * (50.f * Time::DeltaTime());
		}

		tr->SetPosition(pos);

		/*if (mTime > 3.f)
		{
			mState = eState::Walk;
			int direction = rand() % 4;
			mDirection = (eDirection)direction;

			PlayAnimByDirection(mDirection);
			mTime = 0.f;
		}*/
	}

	void CatScript::Move()
	{
		mTime += Time::DeltaTime();
		if (mTime > 2.f)
		{
			int isLayDown = rand() % 2;
			if (isLayDown)
			{
				mState = eState::LayDown;
				mAnimator->PlayAnimation(L"LayDown", false);
			}
			else
			{
				mState = eState::SitDown;
				mAnimator->PlayAnimation(L"SitDown", false);
			}

			mTime = 0.f;
		}
		Transform* tr = GetOwner()->GetComponent<Transform>();
		KMath::Vector2 pos = tr->GetPosition();

		switch (mDirection)
		{
		case eDirection::Left :
			pos.x -= 50.f * Time::DeltaTime();
			break;
		case eDirection::Right :
			pos.x += 50.f * Time::DeltaTime();
			break;
		case eDirection::Down :
			pos.y += 50.f * Time::DeltaTime();
			break;
		case eDirection::Up :
			pos.y -= 50.f * Time::DeltaTime();
			break;
		default :
			assert(false);
			break;
		}

		tr->SetPosition(pos);
	}

	void CatScript::LayDown()
	{
		mTime += Time::DeltaTime();
		if (mTime > 5.f)
		{
			mState = eState::Walk;
			int direction = rand() % 4;
			mDirection = (eDirection)direction;

			PlayAnimByDirection(mDirection);
			mTime = 0.f;
		}
	}

	void CatScript::PlayAnimByDirection(eDirection dir)
	{
		switch (mDirection)
		{
		case eDirection::Left :
			mAnimator->PlayAnimation(L"LeftWalk");
			break;
		case eDirection::Right :
			mAnimator->PlayAnimation(L"RightWalk");
			break;
		case eDirection::Down :
			mAnimator->PlayAnimation(L"DownWalk");
			break;
		case eDirection::Up :
			mAnimator->PlayAnimation(L"UpWalk");
			break;
		default :
			assert(false);
			break;
		}
	}
}

