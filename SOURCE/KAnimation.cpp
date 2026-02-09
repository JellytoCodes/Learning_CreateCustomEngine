#include "KAnimation.h"

#include "GameObject.h"
#include "KAnimator.h"
#include "KRenderer.h"
#include "KTime.h"
#include "KTransform.h"

namespace KEngine
{
	Animation::Animation()
		: Super(eResourceType::Animation),
		mAnimator(nullptr), mTexture(nullptr), mIndex(-1), mTime(0), mbComplete(false)
	{

	}

	Animation::~Animation()
	{

	}

	HRESULT Animation::Save(const std::wstring& path)
	{
		return E_NOTIMPL;
	}

	HRESULT Animation::Load(const std::wstring& path)
	{

		return E_NOTIMPL;
	}

	void Animation::Update()
	{
		if (mbComplete) return;

		mTime += Time::DeltaTime();

		if (mAnimationSheet[mIndex].duration < mTime)
		{
			mTime = 0.f;
			if (mIndex < mAnimationSheet.size() - 1)	mIndex++;
			else										mbComplete = true;
		}
	}

	void Animation::Render()
	{

	}

	void Animation::CreateAnimation(const std::wstring& name, Texture* spriteSheet,
	                                KMath::Vector2 leftTop, KMath::Vector2 size, KMath::Vector2 offset, UINT spriteLength, float duration)
	{
		SetName(name);
		mTexture = spriteSheet;
		for (size_t i = 0 ; i < spriteLength ; i++)
		{
			Sprite sprite = {};

			sprite.leftTop.x = leftTop.x + (size.x * i);
			sprite.leftTop.y = leftTop.y;
			sprite.size = size;
			sprite.offset = offset;
			sprite.duration = duration;

			mAnimationSheet.push_back(sprite);
		}
	}

	void Animation::Reset()
	{
		mTime = 0.f;
		mIndex = 0;
		mbComplete = false;
	}
}
