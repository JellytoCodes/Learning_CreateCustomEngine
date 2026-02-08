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

	void SpriteRenderer::Render()
	{

	}

	void SpriteRenderer::Release()
	{
		mTexture->Release();
	}
}
