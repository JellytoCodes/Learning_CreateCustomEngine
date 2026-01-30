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
		mIndex(-1), mTime(0), mbComplete(false)
	{

	}

	Animation::~Animation()
	{

	}

	HRESULT Animation::Load(const std::wstring& path)
	{

		return S_OK;
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

	void Animation::Render(HDC hdc)
	{
		if (mTexture == nullptr) return;
		auto gameObject = mAnimator.lock()->GetOwner();
		std::shared_ptr<Transform> transform = gameObject.lock()->GetComponent<Transform>();
		KMath::Vector2 pos = transform->GetPosition();

		if (KRenderer::mainCamera)	KRenderer::mainCamera->CalculatePosition(pos);

		// 사용하는 이미지에 알파 채널이 있어야 아래 함수를 사용할 수 있다.
		BLENDFUNCTION blendfunc = {};
		blendfunc.BlendOp = AC_SRC_OVER;
		blendfunc.BlendFlags = 0;
		blendfunc.AlphaFormat = AC_SRC_ALPHA;
		blendfunc.SourceConstantAlpha = 255; // 0(transparent) ~ 255(Opaque)

		Sprite sprite = mAnimationSheet[mIndex];
		HDC imgHdc = mTexture->GetHdc();

		AlphaBlend(hdc, 
		pos.x, 
		pos.y, 
		sprite.size.x * 5, 
		sprite.size.y * 5,
		imgHdc, 
		sprite.leftTop.x, 
		sprite.leftTop.y, 
		sprite.size.x, 
		sprite.size.y, 
		blendfunc);
	}

	void Animation::CreateAnimation(const std::wstring& name, std::shared_ptr<Texture> spriteSheet,
	                                KMath::Vector2 leftTop, KMath::Vector2 size, KMath::Vector2 offset, UINT spriteLength, float duration)
	{
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
