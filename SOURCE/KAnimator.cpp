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
	}

	void Animator::Initialize()
	{
		
	}

	void Animator::Update()
	{
		if (mActiveAnimation)
		{
			mActiveAnimation->Update();
			if (mActiveAnimation->IsComplete() && mbLoop == true)	mActiveAnimation->Reset();
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
		animation->CreateAnimation(name, spriteSheet, leftTop, size, offset, spriteLength, duration);

		animation->SetAnimator(shared_from_this());

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

		mActiveAnimation = animation;
		mActiveAnimation->Reset();
		mbLoop = loop;
	}
}
