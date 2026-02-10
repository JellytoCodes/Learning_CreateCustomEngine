#include "KShader.h"

namespace KEngine
{
	Shader::Shader()
		: Super(eResourceType::Shader)
	{

	}

	Shader::~Shader()
	{

	}

	HRESULT Shader::Save(const std::wstring& path)
	{
		return E_NOTIMPL;
	}

	HRESULT Shader::Load(const std::wstring& path)
	{
		int fineNameBeginOffset = path.rfind(L"\\") + 1;
		int fineNameEndOffset = path.length() - fineNameBeginOffset;
		const std::wstring fileName(path.substr(fineNameBeginOffset, fineNameEndOffset));

		CreateVertexShader(fileName);
		CreatePixelShader(fileName);

		return S_OK;
	}

	void Shader::CreateVertexShader(const std::wstring& fileName)
	{
		DWORD shaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
		shaderFlags |= D3DCOMPILE_DEBUG;
		shaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;

		ID3DBlob* errorBlob = nullptr;
		const std::wstring shaderFilePath = L"..\\SHADER\\";
		HRESULT hr = D3DCompileFromFile(
		(shaderFilePath + fileName + L"VS.hlsl").c_str(), 
		nullptr, 
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		"main",
		"vs_5_0",
		shaderFlags,
		0,
		mVSBlob.GetAddressOf(),
		&errorBlob);

		if (FAILED(hr))
		{
			if (errorBlob)
			{
				OutputDebugStringA((char*)errorBlob->GetBufferPointer());
				errorBlob->Release();
			}
			assert(NULL && "hlsl file have problem check message!");
		}
		assert(SUCCEEDED(
			GraphicDevice_DX11::getInstance().GetDevice()->CreateVertexShader(
			(mVSBlob)->GetBufferPointer(), 
			(mVSBlob)->GetBufferSize(), 
			nullptr, 
			mVS.GetAddressOf())
		));
	}

	void Shader::CreatePixelShader(const std::wstring& fileName)
	{
		DWORD shaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
		shaderFlags |= D3DCOMPILE_DEBUG;
		shaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;

		ID3DBlob* errorBlob = nullptr;
		const std::wstring shaderFilePath = L"..\\SHADER\\";
		HRESULT hr = D3DCompileFromFile(
		(shaderFilePath + fileName + L"PS.hlsl").c_str(), 
		nullptr, 
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		"main",
		"ps_5_0",
		shaderFlags,
		0,
		mPSBlob.GetAddressOf(),
		&errorBlob);

		if (FAILED(hr))
		{
			if (errorBlob)
			{
				OutputDebugStringA((char*)errorBlob->GetBufferPointer());
				errorBlob->Release();
			}
			assert(NULL && "hlsl file have problem check message!");
		}
		assert(SUCCEEDED(
			GraphicDevice_DX11::getInstance().GetDevice()->CreatePixelShader(
			mPSBlob->GetBufferPointer(), 
			mPSBlob->GetBufferSize(),
			nullptr,
			mPS.GetAddressOf())
		));
	}

	void Shader::Bind()
	{
		GraphicDevice_DX11::getInstance().GetDeviceContext()->VSSetShader(GetVertexShader(), 0, 0);
		GraphicDevice_DX11::getInstance().GetDeviceContext()->PSSetShader(GetPixelShader(), 0, 0);
	}
}
