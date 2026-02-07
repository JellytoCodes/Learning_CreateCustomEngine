#pragma once
#include "CommonInclude.h"

namespace KEngine
{
	class GraphicDevice_DX11
	{
	public :
		static GraphicDevice_DX11& getInstance()
		{
			static GraphicDevice_DX11 sInstance;
			return sInstance;
		}

		void Initialize();

		void Draw();

		void CreateDevice();
		void CreateSwapChain();
		void GetBuffer(UINT Buffer, REFIID riid, void** ppSurface);
		void CreateRenderTargetView();
		void CreateDepthStencilView();
		void CreateInputLayout();

		ID3D11Device* GetDevice() const					{ return mDevice.Get(); }
		ID3D11DeviceContext* GetDeviceContext() const		{ return mDeviceContext.Get(); }

	private :
		GraphicDevice_DX11();
		~GraphicDevice_DX11();

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


