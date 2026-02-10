#include "KSpriteRenderer.h"

#include "GameObject.h"
#include "KRenderer.h"
#include "KResources.h"
#include "KTransform.h"
#include "KTexture.h"

namespace KEngine
{
	SpriteRenderer::SpriteRenderer()
		: Super(eComponentType::SpriteRenderer)
	{

	}

	SpriteRenderer::~SpriteRenderer()
	{
		
	}

	void SpriteRenderer::Initialize()
	{
		mMesh = Resources::Find<Mesh>(L"RectMesh");
	}

	void SpriteRenderer::Update()
	{

	}

	void SpriteRenderer::LateUpdate()
	{

	}

	void SpriteRenderer::Render()
	{
		if (mMesh) mMesh->Bind();

		if (mMaterial) mMaterial->BindShader();

		if (mSprite) mSprite->Bind(KGraphics::eShaderStage::PS, (UINT)KGraphics::eTextureType::Albedo);

		if (mMesh) GraphicDevice_DX11::getInstance().DrawIndexed(mMesh->GetIndexCount(), 0, 0);
	}

	void SpriteRenderer::Release()
	{
		
	}
}
