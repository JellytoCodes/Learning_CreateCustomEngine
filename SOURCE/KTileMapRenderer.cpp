#include "KTileMapRenderer.h"

#include "GameObject.h"
#include "KRenderer.h"
#include "KTransform.h"
#include "KTexture.h"

namespace KEngine
{
	KMath::Vector2 TileMapRenderer::TileSize = KMath::Vector2::One;
	KMath::Vector2 TileMapRenderer::OriginTileSize = KMath::Vector2::One;
	KMath::Vector2 TileMapRenderer::SelectedIndex = KMath::Vector2::One;

	TileMapRenderer::TileMapRenderer()
		: Component(eComponentType::SpriteRenderer)
		, mTexture(nullptr),
		mSize(3.f, 3.f), mIndex(0, 0), mTileSize(16.f, 16.f)
	{
		// 타일의 총 개수
		TileSize = mTileSize * mSize;
		OriginTileSize = mTileSize;
	}

	TileMapRenderer::~TileMapRenderer()
	{
		
	}

	void TileMapRenderer::Initialize()
	{


	}
	void TileMapRenderer::Update()
	{

	}

	void TileMapRenderer::LateUpdate()
	{

	}

	void TileMapRenderer::Render(HDC hdc)
	{
		if (mTexture == nullptr) //텍스처 세팅 해주세요!
			assert(false);

		Transform* tr = GetOwner()->GetComponent<Transform>();
		KMath::Vector2 pos = tr->GetPosition();
		float rot = tr->GetRotation();
		KMath::Vector2 scale = tr->GetScale();

		pos = KRenderer::mainCamera->CalculatePosition(pos);
		if (mTexture->GetTextureType() == Texture::eTextureType::BMP)
		{
			if (mTexture->IsAlpha())
			{
				BLENDFUNCTION func = {};
				func.BlendOp = AC_SRC_OVER;
				func.BlendFlags = 0;
				func.AlphaFormat = AC_SRC_ALPHA;
				func.SourceConstantAlpha = 255; // 0(transparent) ~ 255(Opaque)

				AlphaBlend(hdc
					, pos.x, pos.y
					, mTileSize.x * mSize.x * scale.x
					, mTileSize.y * mSize.y * scale.y
					, mTexture->GetHdc()
					, mIndex.x * mTileSize.x, mIndex.y * mTileSize.y
					, mTileSize.x
					, mTileSize.y
					, func);
			}
			else
			{
				TransparentBlt(hdc
					, pos.x, pos.y
					, mTileSize.x * mSize.x * scale.x
					, mTileSize.y * mSize.y * scale.y
					, mTexture->GetHdc()
					, mIndex.x * mTileSize.x, mIndex.y * mTileSize.y
					, mTileSize.x
					, mTileSize.y
					, RGB(255, 0, 255));
			}
		}
		else if (mTexture->GetTextureType() == Texture::eTextureType::PNG)
		{
			// 투명화 시킬 픽셀의 색 범위
			Gdiplus::ImageAttributes imgAtt = {};
			imgAtt.SetColorKey(Gdiplus::Color(230, 230, 230), Gdiplus::Color(255, 255, 255));

			Gdiplus::Graphics graphcis(hdc);

			graphcis.TranslateTransform(pos.x, pos.y);
			graphcis.RotateTransform(rot);
			graphcis.TranslateTransform(-pos.x, -pos.y);

			graphcis.DrawImage(mTexture->GetImage()
				, Gdiplus::Rect
				(
					pos.x, pos.y
					, mTexture->GetWidth() * mSize.x * scale.x
					, mTexture->GetHeight() * mSize.y * scale.y
				)
				, 0, 0
				, mTexture->GetWidth(), mTexture->GetHeight()
				, Gdiplus::UnitPixel
				, nullptr/*&imgAtt*/);
		}
	}

	void TileMapRenderer::Release()
	{
		
	}
}
