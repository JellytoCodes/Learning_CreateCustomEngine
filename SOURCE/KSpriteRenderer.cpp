#include "KSpriteRenderer.h"

#include "GameObject.h"
#include "KRenderer.h"
#include "KTransform.h"
#include "KTexture.h"

namespace KEngine
{
	SpriteRenderer::SpriteRenderer()
		: Super(eComponentType::SpriteRenderer), mSize(KMath::Vector2::One)
	{

	}

	SpriteRenderer::~SpriteRenderer()
	{
		
	}

	void SpriteRenderer::Initialize()
	{

	}

	void SpriteRenderer::Update()
	{

	}

	void SpriteRenderer::LateUpdate()
	{

	}

	void SpriteRenderer::Render(HDC hdc)
	{
		if (mTexture == nullptr) assert(false);

		std::shared_ptr<Transform> transform = GetOwner().lock()->GetComponent<Transform>();
		KMath::Vector2 pos = transform->GetPosition();
		pos = KRenderer::mainCamera->CalculatePosition(pos);
		KMath::Vector2 scale = transform->GetScale();
		float rot = transform->GetRotation();

		if (mTexture->GetTextureType() == KEngine::Texture::eTextureType::BMP)
		{
			if (mTexture->IsAlpha())
			{
				// 사용하는 이미지에 알파 채널이 있어야 아래 함수를 사용할 수 있다.
				BLENDFUNCTION blendFunc;
				blendFunc.BlendOp = AC_SRC_OVER;
				blendFunc.BlendFlags = 0;
				blendFunc.AlphaFormat = AC_SRC_ALPHA;
				blendFunc.SourceConstantAlpha = 255; // 0(transparent) ~ 255(Opaque)

				AlphaBlend(hdc, 
				static_cast<int>(pos.x), 
				static_cast<int>(pos.y), 
				static_cast<int>(mTexture->GetWidth() * mSize.x * scale.x), 
				static_cast<int>(mTexture->GetHeight() * mSize.y * scale.y),
				mTexture->GetHdc(),
				0, 
				0, 
				static_cast<int>(mTexture->GetWidth()), 
				static_cast<int>(mTexture->GetHeight()), 
				blendFunc);	
			}
			else
			{
				TransparentBlt(hdc,
				static_cast<int>(pos.x),
				static_cast<int>(pos.y),
				static_cast<int>(mTexture->GetWidth() * mSize.x * scale.x),
				static_cast<int>(mTexture->GetHeight() * mSize.y * scale.y),
				mTexture->GetHdc(),
				0, 
				0, 
				static_cast<int>(mTexture->GetWidth()), 
				static_cast<int>(mTexture->GetHeight()), 
				RGB(255, 0, 255));
			}
		}
		else if (mTexture->GetTextureType() == KEngine::Texture::eTextureType::PNG)
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
				mTexture->GetImage().get(), 
				Gdiplus::Rect(pos.x, pos.y, mTexture->GetWidth() * mSize.x, mTexture->GetHeight() * mSize.y),
				0,
				0,
				mTexture->GetWidth() * mSize.x * scale.x,
				mTexture->GetHeight()* mSize.y * scale.y,
				Gdiplus::UnitPixel,
				nullptr/*&imgAttribute*/ 
				// 일반적으론 png에 Alpha데이터가 들어가 있기 때문에 수동으로 조정할 일이 잘 없다.
				);
		}
	}

	void SpriteRenderer::Release()
	{
		mTexture->Release();
	}
}
