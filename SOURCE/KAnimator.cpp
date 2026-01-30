#include "KAnimator.h"
#include "KTexture.h"

namespace KEngine
{
	Animator::Animator()
		: Super(eComponentType::Animator),
		mbLoop(false)
	{

	}

	Animator::~Animator()
	{
		for (auto& iter : mEvents)
		{
			delete iter.second;
		}
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

	void Animator::Render(HDC hdc)
	{
		if (mActiveAnimation)	mActiveAnimation->Render(hdc);
	}

	void Animator::Release()
	{

	}

	void Animator::CreateAnimation(const std::wstring& name, std::shared_ptr<Texture> spriteSheet,
		KMath::Vector2 leftTop, KMath::Vector2 size, KMath::Vector2 offset, UINT spriteLength, float duration)
	{
		std::shared_ptr<Animation> animation = FindAnimation(name);
		if (animation != nullptr) return;

		animation = std::make_shared<Animation>();
		animation->SetName(name);
		animation->CreateAnimation(name, spriteSheet, leftTop, size, offset, spriteLength, duration);

		animation->SetAnimator(shared_from_this());

		Events* events = new Events();
		mEvents.insert(std::make_pair(name, events));

		mAnimations.insert(std::make_pair(name, animation));
	}

	std::shared_ptr<Animation> Animator::FindAnimation(const std::wstring& name)
	{
		auto It = mAnimations.find(name);

		return It == mAnimations.end() ? nullptr : It->second;
	}

	void Animator::PlayAnimation(const std::wstring& name, bool loop)
	{
		std::shared_ptr<Animation> animation = FindAnimation(name);
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

		return It == mEvents.end() ? nullptr : It->second;
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
