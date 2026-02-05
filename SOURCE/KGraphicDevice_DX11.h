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


