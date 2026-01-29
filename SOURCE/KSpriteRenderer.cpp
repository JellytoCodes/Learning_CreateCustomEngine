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

		std::shared_ptr<Transform> tr = GetOwner().lock()->GetComponent<Transform>();
		KMath::Vector2 pos = tr->GetPosition();
		pos = KRenderer::mainCamera->CalculatePosition(pos);

		if (mTexture->GetTextureType() == KEngine::Texture::eTextureType::BMP)
		{
			
			TransparentBlt(
			hdc, pos.x, pos.y, mTexture->GetWidth(), mTexture->GetHeight(), 
			mTexture->GetHdc(), 0, 0 , mTexture->GetWidth(), mTexture->GetHeight(),
			RGB(255, 0, 255));
		}
		else if (mTexture->GetTextureType() == KEngine::Texture::eTextureType::PNG)
		{
			Gdiplus::Graphics graphics(hdc);
			graphics.DrawImage(
				mTexture->GetImage().get(), 
				Gdiplus::Rect(pos.x, pos.y, mTexture->GetWidth() * mSize.x, mTexture->GetHeight() * mSize.y));
		}
		

	}

	void SpriteRenderer::Release()
	{
		mTexture->Release();
	}
}
