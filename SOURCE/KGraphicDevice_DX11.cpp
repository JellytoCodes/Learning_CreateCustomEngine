#include "KGraphicDevice_DX11.h"
#include "KApplication.h"
#include "KMaterial.h"
#include "KRenderer.h"
#include "KResources.h"
#include "KShader.h"
#include "KVertexBuffer.h"

extern KEngine::Application application;

namespace KEngine
{
	GraphicDevice_DX11::GraphicDevice_DX11()
	{
		
	}

	GraphicDevice_DX11::~GraphicDevice_DX11()
	{
		
	}

	void GraphicDevice_DX11::Initialize()
	{
		CreateDevice();
		KRenderer::Initialize();
		CreateSwapChain();
		GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)mRenderTarget.GetAddressOf());
		CreateRenderTargetView();
		CreateInputLayout();
		CreateDepthStencilView();
	}

	void GraphicDevice_DX11::Draw()
	{
		mDeviceContext->IASetInputLayout(KRenderer::inputLayouts.Get());

		Mesh* mesh = Resources::Find<Mesh>(L"RectMesh");
		mesh->Bind();

		KMath::Vector4 pos(0.f, 0.0f, 0.0f, 1.0f);
		KRenderer::constantBuffers[(UINT)KGraphics::eCBType::Transform].SetData(&pos);
		KRenderer::constantBuffers[(UINT)KGraphics::eCBType::Transform].BindConstantBuffer(KGraphics::eShaderStage::VS);

		Material* material = KEngine::Resources::Find<Material>(L"SpriteMaterial");
		material->Bind();

		Texture* texture = Resources::Find<Texture>(L"Player");
		if (texture) texture->Bind(KGraphics::eShaderStage::PS, 0);
	}

	void GraphicDevice_DX11::CreateDevice()
	{
		D3D_FEATURE_LEVEL featureLevels[] = { D3D_FEATURE_LEVEL_11_0 };
		UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#if defined(DEBUG) || defined(_DEBUG)
		creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

		assert(SUCCEEDED(
			D3D11CreateDevice(
			0, 
			D3D_DRIVER_TYPE_HARDWARE, 
			0, 
			creationFlags, 
			featureLevels, 
			ARRAYSIZE(featureLevels),
			D3D11_SDK_VERSION,
			mDevice.GetAddressOf(),
			0,
			mDeviceContext.GetAddressOf())
		));
	}

	void GraphicDevice_DX11::CreateSwapChain()
	{
		DXGI_SWAP_CHAIN_DESC desc;
		ZeroMemory(&desc, sizeof(DXGI_SWAP_CHAIN_DESC));

		desc.OutputWindow = application.GetHwnd();
		desc.Windowed = true;
		desc.BufferCount = 2;
		desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
		desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

		desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		desc.BufferDesc.Width = application.GetViewSize().width;
		desc.BufferDesc.Height = application.GetViewSize().height;
		desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		desc.BufferDesc.RefreshRate.Numerator = 144;
		desc.BufferDesc.RefreshRate.Denominator = 1;
		desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		desc.SampleDesc.Count = 1;
		desc.SampleDesc.Quality = 0;

		// 4X MSAA 멀티샘플 기능 지원 유무 체크
		/*UINT quality = 0;
		mDevice->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4, &quality);

		if (quality > 0)
		{
			desc.SampleDesc.Count = 4;
			desc.SampleDesc.Quality = quality - 1;
		}*/
		
		Microsoft::WRL::ComPtr<IDXGIDevice>		pDXGIDevice = nullptr;
		Microsoft::WRL::ComPtr<IDXGIAdapter>	pAdapter = nullptr;
		Microsoft::WRL::ComPtr<IDXGIFactory>	pFactory = nullptr;

		assert(SUCCEEDED(
			mDevice->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(pDXGIDevice.GetAddressOf()))
		));
		assert(SUCCEEDED(
			pDXGIDevice->GetParent(__uuidof(IDXGIAdapter), reinterpret_cast<void**>(pAdapter.GetAddressOf()))
		));
		assert(SUCCEEDED(
			pAdapter->GetParent(__uuidof(IDXGIFactory), reinterpret_cast<void**>(pFactory.GetAddressOf()))
		));
		assert(SUCCEEDED(
			pFactory->CreateSwapChain(mDevice.Get(), &desc, mSwapChain.GetAddressOf())
		));
	}

	void GraphicDevice_DX11::GetBuffer(UINT Buffer, const IID& riid, void** ppSurface)
	{
		assert(SUCCEEDED(
			mSwapChain->GetBuffer(Buffer, riid, ppSurface)
		));
	}

	void GraphicDevice_DX11::CreateRenderTargetView()
	{
		// D3D11_RENDER_TARGET_VIEW_DESC desc;
		assert(SUCCEEDED(
			mDevice->CreateRenderTargetView(mRenderTarget.Get(), nullptr, mRTV.GetAddressOf())
		));
	}

	void GraphicDevice_DX11::CreateDepthStencilView()
	{
		D3D11_TEXTURE2D_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_TEXTURE2D_DESC));

		DXGI_SWAP_CHAIN_DESC swapDesc;
		mSwapChain->GetDesc(&swapDesc);

		desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.Width = application.GetViewSize().width;
		desc.Height = application.GetViewSize().height;
		desc.ArraySize = 1;
		desc.SampleDesc.Count = swapDesc.SampleDesc.Count;
		desc.SampleDesc.Quality = swapDesc.SampleDesc.Quality;

		assert(SUCCEEDED(
			mDevice->CreateTexture2D(&desc, nullptr, mDepthStencil.GetAddressOf())
		));
		assert(SUCCEEDED(
			mDevice->CreateDepthStencilView(mDepthStencil.Get(), nullptr, mDSV.GetAddressOf())
		));
	}

	void GraphicDevice_DX11::CreateInputLayout()
	{
		DWORD shaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
		shaderFlags |= D3DCOMPILE_DEBUG;
		shaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;

		D3D11_INPUT_ELEMENT_DESC inputLayoutDesces[3] = {};

		inputLayoutDesces[0].AlignedByteOffset = 0;
		inputLayoutDesces[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
		inputLayoutDesces[0].InputSlot = 0;
		inputLayoutDesces[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		inputLayoutDesces[0].SemanticName = "POSITION";
		inputLayoutDesces[0].SemanticIndex = 0;

		inputLayoutDesces[1].AlignedByteOffset = 12;
		inputLayoutDesces[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		inputLayoutDesces[1].InputSlot = 0;
		inputLayoutDesces[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		inputLayoutDesces[1].SemanticName = "COLOR";
		inputLayoutDesces[1].SemanticIndex = 0;

		inputLayoutDesces[2].AlignedByteOffset = 28; //12 + 16
		inputLayoutDesces[2].Format = DXGI_FORMAT_R32G32_FLOAT;
		inputLayoutDesces[2].InputSlot = 0;
		inputLayoutDesces[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		inputLayoutDesces[2].SemanticName = "TEXCOORD";
		inputLayoutDesces[2].SemanticIndex = 0;

		{
			Shader* shader = Resources::Find<Shader>(L"SpriteShader");
					mDevice->CreateInputLayout(
			inputLayoutDesces, 
			3,
			shader->GetVSBlob()->GetBufferPointer(),
			shader->GetVSBlob()->GetBufferSize(),
			KRenderer::inputLayouts.GetAddressOf());
		}
	}

	void GraphicDevice_DX11::BindSampler(KGraphics::eShaderStage stage, UINT StartSlot, UINT NumSamplers, ID3D11SamplerState* const* ppSamplers)
	{
		if (KGraphics::eShaderStage::VS == stage)
			mDeviceContext->VSSetSamplers(StartSlot, NumSamplers, ppSamplers);

		if (KGraphics::eShaderStage::HS == stage)
			mDeviceContext->HSSetSamplers(StartSlot, NumSamplers, ppSamplers);

		if (KGraphics::eShaderStage::DS == stage)
			mDeviceContext->DSSetSamplers(StartSlot, NumSamplers, ppSamplers);

		if (KGraphics::eShaderStage::GS == stage)
			mDeviceContext->GSSetSamplers(StartSlot, NumSamplers, ppSamplers);

		if (KGraphics::eShaderStage::PS == stage)
			mDeviceContext->PSSetSamplers(StartSlot, NumSamplers, ppSamplers);
	}

	void GraphicDevice_DX11::BindSamplers(UINT StartSlot, UINT NumSamplers, ID3D11SamplerState* const* ppSamplers)
	{
		BindSampler(KGraphics::eShaderStage::VS, StartSlot, NumSamplers, ppSamplers);
		BindSampler(KGraphics::eShaderStage::HS, StartSlot, NumSamplers, ppSamplers);
		BindSampler(KGraphics::eShaderStage::DS, StartSlot, NumSamplers, ppSamplers);
		BindSampler(KGraphics::eShaderStage::GS, StartSlot, NumSamplers, ppSamplers);
		BindSampler(KGraphics::eShaderStage::PS, StartSlot, NumSamplers, ppSamplers);
	}

	void GraphicDevice_DX11::BindViewPort()
	{
		D3D11_VIEWPORT viewPort =
		{
			0, 0, (FLOAT)application.GetViewSize().width, (FLOAT)application.GetViewSize().height,
			0.0f, 1.0f
		};
		mDeviceContext->RSSetViewports(1, &viewPort);
	}

	void GraphicDevice_DX11::BindRenderTargets(UINT NumViews, ID3D11RenderTargetView* const* ppRenderTargetViews, ID3D11DepthStencilView* pDepthStencilView)
	{
		mDeviceContext->OMSetRenderTargets(1, ppRenderTargetViews, pDepthStencilView);
	}

	void GraphicDevice_DX11::BindDefaultRenderTarget()
	{
		mDeviceContext->OMSetRenderTargets(1, mRTV.GetAddressOf(), mDSV.Get());
	}

	void GraphicDevice_DX11::ClearRenderTargetView()
	{
		FLOAT backgroundColor[4] = {0.2f, 0.2f, 0.2f, 1.f};
		mDeviceContext->ClearRenderTargetView(mRTV.Get(), backgroundColor);
	}

	void GraphicDevice_DX11::ClearDepthStencilView()
	{
		mDeviceContext->ClearDepthStencilView(mDSV.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.f, 0);
	}

	void GraphicDevice_DX11::DrawIndexed(UINT IndexCount, UINT StartIndexLocation, INT BaseVertexLocation)
	{
		mDeviceContext->DrawIndexed(IndexCount,StartIndexLocation, BaseVertexLocation);
	}

	void GraphicDevice_DX11::Present()
	{
		mSwapChain->Present(1, 0);
	}
}
