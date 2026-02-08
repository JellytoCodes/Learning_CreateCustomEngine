#include "KTile.h"

#include "KTileMapRenderer.h"
#include "KTransform.h"

namespace KEngine
{
	void Tile::Initialize()
	{
		GameObject::Initialize();
	}

	void Tile::Update()
	{
		GameObject::Update();
	}

	void Tile::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void Tile::Render()
	{
		GameObject::Render();
	}

	void Tile::SetIndexPosition(int x, int y)
	{	
		Transform* tr = GetComponent<Transform>();
		KMath::Vector2 pos;

		pos.x = x * TileMapRenderer::TileSize.x;
		pos.y = y * TileMapRenderer::TileSize.y;

		tr->SetPosition(pos);
	}
}
