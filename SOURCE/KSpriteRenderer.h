#pragma once
#include "KComponent.h"
#include "KMaterial.h"
#include "KMesh.h"

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
		void Render()  override;
		void Release() override;

		void SetSprite(Texture* sprite)			{ mSprite = sprite; }
		void SetMaterial(Material* material)	{ mMaterial = material; }
	private:
		Texture* mSprite;
		Material* mMaterial;
		Mesh* mMesh;
	};
}

