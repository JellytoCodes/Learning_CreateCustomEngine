#pragma once
#include "KComponent.h"

namespace KEngine
{
	class Texture;

	class TileMapRenderer :public Component
	{
		using Super = Component;

	public:
		TileMapRenderer();
		virtual ~TileMapRenderer();

		void	Initialize() override;
		void	Update()  override;
		void	LateUpdate()  override;
		void	Render(HDC hdc)  override;
		void	Release() override;

		void	SetTexture(Texture* texture) { mTexture = texture; }
		void	SetSize(KMath::Vector2 size) { mSize = size; }

	private:
		Texture*			mTexture;
		KMath::Vector2		mSize;
		KMath::Vector2		mTileSize;
		KMath::Vector2		mIndex;
	};	
}
