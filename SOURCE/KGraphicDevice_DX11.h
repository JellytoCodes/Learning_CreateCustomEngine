#pragma once

#include <d3d11.h>
#include <d3dcompiler.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

#include "CommonInclude.h"

namespace KEngine
{
	class GraphicDevice_DX11
	{
	public :
		GraphicDevice_DX11();
		~GraphicDevice_DX11();

		void Initialize();

		void Draw();

		void CreateDevice();
		void CreateSwapChain();
		void GetBuffer(UINT Buffer, REFIID riid, void** ppSurface);
		void CreateRenderTargetView();
		void CreateDepthStencilView();
		void CreateVertexShader(const std::wstring& fileName);
		void CreatePixelShader(const std::wstring& fileName);
		void CreateInputLayout();
		void CreateVertexBuffer();
		void CreateIndexBuffer();
		void CreateConstantBuffer();

		void BindConstantBuffer(KGraphics::eShaderStage stage, KGraphics::eCBType type, ID3D11Buffer* buffer);

	private :
		Microsoft::WRL::ComPtr<ID3D11Device>				mDevice;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext>			mDeviceContext;
		Microsoft::WRL::ComPtr<ID3D11Texture2D>				mRenderTarget;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView>		mRTV;
		Microsoft::WRL::ComPtr<ID3D11Texture2D>				mDepthStencil;	// Buffer
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView>		mDSV;

		Microsoft::WRL::ComPtr<IDXGISwapChain>				mSwapChain;
		Microsoft::WRL::ComPtr<ID3D11SamplerState>			mSamplerState;
	};
}


