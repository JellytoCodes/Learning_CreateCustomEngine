#pragma once
#include "KGraphicDevice_DX11.h"

#include "KResource.h"

namespace KEngine
{
	class Shader : public Resource
	{
		using Super = Resource;
	public :
		Shader();
		virtual ~Shader();

		HRESULT Save(const std::wstring& path) override;
		HRESULT Load(const std::wstring& path) override;

		void CreateVertexShader(const std::wstring& fileName);
		void CreatePixelShader(const std::wstring& fileName);

		ID3D11VertexShader*		GetVertexShader() const { return mVS.Get(); }
		ID3DBlob*				GetVSBlob() const { return mVSBlob.Get(); }

		ID3D11PixelShader*		GetPixelShader() const { return mPS.Get(); }

		void Bind();

	private :
		Microsoft::WRL::ComPtr<ID3DBlob>				mVSBlob;
		Microsoft::WRL::ComPtr<ID3D11VertexShader>		mVS;

		Microsoft::WRL::ComPtr<ID3DBlob>				mHSBlob;
		Microsoft::WRL::ComPtr<ID3D11HullShader>		mHS;

		Microsoft::WRL::ComPtr<ID3DBlob>				mDSBlob;
		Microsoft::WRL::ComPtr<ID3D11DomainShader>		mDS;

		Microsoft::WRL::ComPtr<ID3DBlob>				mGSBlob;
		Microsoft::WRL::ComPtr<ID3D11GeometryShader>	mGS;

		Microsoft::WRL::ComPtr<ID3DBlob>				mPSBlob;
		Microsoft::WRL::ComPtr<ID3D11PixelShader>		mPS;
	};	
}

