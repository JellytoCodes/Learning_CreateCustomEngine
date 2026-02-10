#pragma once
#include "KResource.h"
#include "KResource.h"
#include "KGraphicDevice_DX11.h"

#include <DirectXTex.h>
#include <DirectXTex.inl>
#include <DirectXTexEXR.h>


namespace KEngine
{
	class Texture : public KEngine::Resource
	{
		using Super = Resource;

	public :
		enum class eTextureType
		{
			BMP,
			PNG,
			None,
		};

		Texture();
		virtual ~Texture();

		HRESULT				Save(const std::wstring& path) override;
		HRESULT				Load(const std::wstring& path) override;

		void				Release() override;

		void Bind(KGraphics::eShaderStage stage, UINT startSlot);

	private :
		ScratchImage										mImage;

		D3D11_TEXTURE2D_DESC								mDesc;
		Microsoft::WRL::ComPtr<ID3D11Texture2D>				mTexture;

		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>	mSRV;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView>		mRTV;
	};	
}


