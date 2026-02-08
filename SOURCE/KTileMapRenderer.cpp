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

	void TileMapRenderer::Render()
	{

	}

	void TileMapRenderer::Release()
	{
		
	}
}
