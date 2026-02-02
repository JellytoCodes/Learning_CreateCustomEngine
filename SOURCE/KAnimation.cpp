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
		GameObject* gameObject = mAnimator->GetOwner();
		Transform* transform = gameObject->GetComponent<Transform>();
		KMath::Vector2 pos = transform->GetPosition();
		KMath::Vector2 scale = transform->GetScale();
		float rot = transform->GetRotation();

		if (KRenderer::mainCamera)	pos = KRenderer::mainCamera->CalculatePosition(pos);

		Texture::eTextureType type = mTexture->GetTextureType();

		Sprite sprite = mAnimationSheet[mIndex];

		if (type == Texture::eTextureType::BMP)
		{
			HDC imgHdc = mTexture->GetHdc();

			if (mTexture->IsAlpha())
			{
				// 사용하는 이미지에 알파 채널이 있어야 아래 함수를 사용할 수 있다.
				BLENDFUNCTION blendFunc;
				blendFunc.BlendOp = AC_SRC_OVER;
				blendFunc.BlendFlags = 0;
				blendFunc.AlphaFormat = AC_SRC_ALPHA;
				blendFunc.SourceConstantAlpha = 255; // 0(transparent) ~ 255(Opaque)

				AlphaBlend(hdc, 
				static_cast<int>(pos.x - (sprite.size.x / 2.f) + sprite.offset.x), 
				static_cast<int>(pos.y - (sprite.size.y / 2.f) + sprite.offset.y), 
				static_cast<int>(sprite.size.x * scale.x), 
				static_cast<int>(sprite.size.y * scale.y),
				imgHdc,
				static_cast<int>(sprite.leftTop.x), 
				static_cast<int>(sprite.leftTop.y), 
				static_cast<int>(sprite.size.x), 
				static_cast<int>(sprite.size.y), 
				blendFunc);	
			}
			else
			{
				TransparentBlt(hdc,
				static_cast<int>(pos.x - (sprite.size.x / 2.0f)),
				static_cast<int>(pos.y - (sprite.size.y / 2.0f)),
				static_cast<int>(sprite.size.x * scale.x),
				static_cast<int>(sprite.size.y * scale.y),
				imgHdc,
				static_cast<int>(sprite.leftTop.x),
				static_cast<int>(sprite.leftTop.y),
				static_cast<int>(sprite.size.x),
				static_cast<int>(sprite.size.y),
				RGB(255, 0, 255));
			}
		}
		else if (type == Texture::eTextureType::PNG)
		{
			// 내가 원하는 픽셀을 투명화 시킬 때
			Gdiplus::ImageAttributes imgAttribute;

			// 투명화시킬 픽셀의 색 범위
			imgAttribute.SetColorKey(
			Gdiplus::Color(230, 230, 230), 
			Gdiplus::Color( 255, 255, 255));

			Gdiplus::Graphics graphics(hdc);

			graphics.TranslateTransform(pos.x, pos.y);
			graphics.RotateTransform(rot);
			graphics.TranslateTransform(-pos.x, -pos.y);

			graphics.DrawImage(
				mTexture->GetImage(),
				Gdiplus::Rect(pos.x - (sprite.size.x / 2.f), pos.y - (sprite.size.y / 2.f), sprite.size.x, sprite.size.y),
				sprite.leftTop.x * scale.x, 
				sprite.leftTop.y * scale.y,
				sprite.size.x,
				sprite.size.y,
				Gdiplus::UnitPixel,
				&imgAttribute);
		}
	}

	void Animation::CreateAnimation(const std::wstring& name, Texture* spriteSheet,
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
