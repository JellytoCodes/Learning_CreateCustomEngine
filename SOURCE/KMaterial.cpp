#include "KMaterial.h"

namespace KEngine
{
	Material::Material()
		: Resource(KEngine::eResourceType::Material)
		, mMode(KGraphics::eRenderingMode::Opaque)
	{

	}

	Material::~Material()
	{

	}

	HRESULT Material::Save(const std::wstring& path)
	{
		return E_NOTIMPL;
	}

	HRESULT Material::Load(const std::wstring& path)
	{
		return E_NOTIMPL;
	}

	void Material::Bind()
	{
		if (mShader) mShader->Bind();

		if (mAlbedoTexture) mAlbedoTexture->Bind(KGraphics::eShaderStage::PS, (UINT)KGraphics::eTextureType::Albedo);
	}

	void Material::BindShader()
	{
		if (mShader) mShader->Bind();
	}

	void Material::BindTextures()
	{
		if (mAlbedoTexture) mAlbedoTexture->Bind(KGraphics::eShaderStage::PS, (UINT)KGraphics::eTextureType::Albedo);
	}
}
