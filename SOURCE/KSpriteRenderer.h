#pragma once
#include "KComponent.h"

namespace KEngine
{
	class Texture;

	class SpriteRenderer : public Component
	{
		using Super = Component;

	public:
		SpriteRenderer();
		virtual ~SpriteRenderer();

		void Initialize() override;
		void Update()  override;
		void LateUpdate()  override;
		void Render(HDC hdc)  override;
		void Release() override;

		void SetTexture(Texture* texture) { mTexture = texture; }
		void SetSize(KMath::Vector2 size) { mSize = size; }

	private:
		Texture* mTexture;
		KMath::Vector2 mSize;
	};
}

