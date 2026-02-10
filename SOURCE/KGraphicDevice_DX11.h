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

		void CreateDevice();
		void CreateSwapChain();
		void GetBuffer(UINT Buffer, REFIID riid, void** ppSurface);
		void CreateRenderTargetView();
		void CreateDepthStencilView();
		void CreateInputLayout();

		ID3D11Device* GetDevice() const					{ return mDevice.Get(); }
		ID3D11DeviceContext* GetDeviceContext() const		{ return mDeviceContext.Get(); }

		void BindSampler(KGraphics::eShaderStage stage, UINT StartSlot, UINT NumSamplers, ID3D11SamplerState* const* ppSamplers);
		void BindSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState* const* ppSamplers);

		void BindViewPort();
		void BindRenderTargets(UINT NumViews = 1, ID3D11RenderTargetView* const* ppRenderTargetViews = nullptr, ID3D11DepthStencilView* pDepthStencilView = nullptr);
		void BindDefaultRenderTarget();

		void ClearRenderTargetView();
		void ClearDepthStencilView();

		void Draw();
		void DrawIndexed(UINT IndexCount, UINT StartIndexLocation, INT BaseVertexLocation);
		void Present();
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


