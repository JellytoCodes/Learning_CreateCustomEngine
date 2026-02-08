#include "KAnimator.h"
#include "KTexture.h"
#include "KResources.h"

namespace KEngine
{
	Animator::Animator()
		: Super(eComponentType::Animator),
		mActiveAnimation(nullptr), mbLoop(false)
	{

	}

	Animator::~Animator()
	{

	}

	void Animator::Initialize()
	{
		
	}

	void Animator::Update()
	{
		if (mActiveAnimation)
		{
			mActiveAnimation->Update();

			Events* events = FindEvents(mActiveAnimation->GetName());

			if (mActiveAnimation->IsComplete())
			{
				if (events)			events->completeEvent();
				if (mbLoop == true)	mActiveAnimation->Reset();
			}
		}
	}

	void Animator::LateUpdate()
	{
		
	}

	void Animator::Render()
	{
		
	}

	/* WINAPI를 활용한 렌더링
	void Animator::Render(HDC hdc)
	{
		if (mActiveAnimation)	mActiveAnimation->Render(hdc);
	}
	*/

	void Animator::Release()
	{

	}

	void Animator::CreateAnimation(const std::wstring& name, Texture* spriteSheet,
		KMath::Vector2 leftTop, KMath::Vector2 size, KMath::Vector2 offset, UINT spriteLength, float duration)
	{
		if (FindAnimation(name) != nullptr) return;

		auto animation = std::make_unique<Animation>();
		animation->SetName(name);
		animation->CreateAnimation(name, spriteSheet, leftTop, size, offset, spriteLength, duration);
		animation->SetAnimator(this);

		mEvents.insert(std::make_pair(name, std::make_unique<Events>()));
		mAnimations.insert(std::make_pair(name, std::move(animation)));
	}

	void Animator::CreateAnimationByFolder()
	{

	}

	Animation* Animator::FindAnimation(const std::wstring& name)
	{
		auto it = mAnimations.find(name);
		return it == mAnimations.end() ? nullptr : it->second.get();
	}

	void Animator::PlayAnimation(const std::wstring& name, bool loop)
	{
		Animation* animation = FindAnimation(name);
		if (animation == nullptr) return;

		if (mActiveAnimation)
		{
			// Current Event
			if (Events* events = FindEvents(mActiveAnimation->GetName()))	events->endEvent();

			// Next Event
			if (Events* events = FindEvents(animation->GetName()))			events->startEvent();	
		}

		mActiveAnimation = animation;
		mActiveAnimation->Reset();
		mbLoop = loop;
	}

	Animator::Events* Animator::FindEvents(const std::wstring& name)
	{
		auto It = mEvents.find(name);

		return It == mEvents.end() ? nullptr : It->second.get();
	}

	std::function<void()>& Animator::GetStartEvent(const std::wstring& name)
	{
		Events* events = FindEvents(name);
		return events->startEvent.mEvent;
	}

	std::function<void()>& Animator::GetCompleteEvent(const std::wstring& name)
	{
		Events* events = FindEvents(name);
		return events->completeEvent.mEvent;
	}

	std::function<void()>& Animator::GetEndEvent(const std::wstring& name)
	{
		Events* events = FindEvents(name);
		return events->endEvent.mEvent;
	}
}
