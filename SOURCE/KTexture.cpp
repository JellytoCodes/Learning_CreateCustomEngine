#include "KTexture.h"

#include <memory>

#include "KApplication.h"
#include "KResources.h"

extern KEngine::Application application;

namespace KEngine
{
	Texture::Texture()
    : Super(KEngine::eResourceType::Texture), mDesc{}
	{

	}

	Texture::~Texture()
	{

	}

	HRESULT Texture::Save(const std::wstring& path)
	{
		return E_NOTIMPL;
	}

	HRESULT Texture::Load(const std::wstring& path)
	{
		std::wstring ext = path.substr(path.find_last_of(L".") + 1);

		if (ext == L".dds" || ext == L".DDS")
		{
			if (FAILED(LoadFromDDSFile(path.c_str(), DDS_FLAGS::DDS_FLAGS_NONE, nullptr, mImage)))
				return S_FALSE;
		}

		else if (ext == L".tga" || ext == L".TGA")
		{
			if (FAILED(LoadFromTGAFile(path.c_str(), nullptr, mImage)))
				return S_FALSE;
		}
		else // WIC (png, jpg, jpeg, bmp )
		{
			if (FAILED(LoadFromWICFile(path.c_str(), WIC_FLAGS::WIC_FLAGS_NONE, nullptr, mImage)))
				return S_FALSE;
		}
		
		HRESULT hr = CreateShaderResourceView(
			GraphicDevice_DX11::getInstance().GetDevice(),
			mImage.GetImages(),
			mImage.GetImageCount(),
			mImage.GetMetadata(),
			mSRV.GetAddressOf());
		assert(SUCCEEDED(hr));

		mSRV->GetResource((ID3D11Resource**)mTexture.GetAddressOf());

		return S_OK;
	}

	void Texture::Release()
	{

	}

	void Texture::Bind(KGraphics::eShaderStage stage, UINT startSlot)
	{
		if ((UINT)KGraphics::eShaderStage::VS & (UINT)stage)
			GraphicDevice_DX11::getInstance().GetDeviceContext()->VSSetShaderResources(startSlot, 1, mSRV.GetAddressOf());

		if ((UINT)KGraphics::eShaderStage::HS & (UINT)stage)
			GraphicDevice_DX11::getInstance().GetDeviceContext()->HSSetShaderResources(startSlot, 1, mSRV.GetAddressOf());

		if ((UINT)KGraphics::eShaderStage::DS & (UINT)stage)
			GraphicDevice_DX11::getInstance().GetDeviceContext()->DSSetShaderResources(startSlot, 1, mSRV.GetAddressOf());

		if ((UINT)KGraphics::eShaderStage::GS & (UINT)stage)
			GraphicDevice_DX11::getInstance().GetDeviceContext()->GSSetShaderResources(startSlot, 1, mSRV.GetAddressOf());

		if ((UINT)KGraphics::eShaderStage::PS & (UINT)stage)
			GraphicDevice_DX11::getInstance().GetDeviceContext()->PSSetShaderResources(startSlot, 1, mSRV.GetAddressOf());

		if ((UINT)KGraphics::eShaderStage::CS & (UINT)stage)
			GraphicDevice_DX11::getInstance().GetDeviceContext()->CSSetShaderResources(startSlot, 1, mSRV.GetAddressOf());
	}
}
