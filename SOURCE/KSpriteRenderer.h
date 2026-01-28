#pragma once
#include "KComponent.h"
#include "KTexture.h"

namespace KEngine
{
	class SpriteRenderer : public Component
	{
	public:
		SpriteRenderer();
		virtual ~SpriteRenderer();

		void Initialize() override;
		void Update()  override;
		void LateUpdate()  override;
		void Render(HDC hdc)  override;
		void Release() override;

		void SetTexture(std::shared_ptr<Texture> texture) { mTexture = texture; }
		void SetSize(KMath::Vector2 size) { mSize = size; }

	private:
		std::shared_ptr<Texture> mTexture;
		KMath::Vector2 mSize;
	};
}

