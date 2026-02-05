#include "KGraphicDevice_DX11.h"
#include "KApplication.h"
#include "KRenderer.h"

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
		D3D_FEATURE_LEVEL featureLevels[] = { D3D_FEATURE_LEVEL_11_0 };
		UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#if defined(DEBUG) || defined(_DEBUG)
		creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

		{ // CreateDevice
			HRESULT hr = D3D11CreateDevice(
			0, 
			D3D_DRIVER_TYPE_HARDWARE, 
			0, 
			creationFlags, 
			featureLevels, 
			ARRAYSIZE(featureLevels),
			D3D11_SDK_VERSION,
			mDevice.GetAddressOf(),
			0,
			mDeviceContext.GetAddressOf());

			assert(SUCCEEDED(hr));	
		}

		{ // CreateSwap
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

			// 4X MSAA 멀티샘플 기능 지원 유무 체크
			UINT quality = 0;
			mDevice->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4, &quality);

			if (quality > 0)
			{
				desc.SampleDesc.Count = 4;
				desc.SampleDesc.Quality = quality - 1;
			}
			else
			{
				desc.SampleDesc.Count = 1;
				desc.SampleDesc.Quality = 0;
			}

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

			mSwapChain->GetBuffer(0, _uuidof(ID3D11Texture2D), reinterpret_cast<void**>(mRenderTarget.GetAddressOf()));
			mDevice->CreateRenderTargetView(mRenderTarget.Get(), nullptr, mRTV.GetAddressOf());
		}

		{ // Texture
			D3D11_TEXTURE2D_DESC desc;
			ZeroMemory(&desc, sizeof(D3D11_TEXTURE2D_DESC));

			desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
			desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
			desc.Usage = D3D11_USAGE_DEFAULT;
			desc.Width = application.GetViewSize().width;
			desc.Height = application.GetViewSize().height;
			desc.ArraySize = 1;
			desc.SampleDesc.Count = 1;
			desc.SampleDesc.Quality = 0;
			assert(SUCCEEDED(
				mDevice->CreateTexture2D(&desc, nullptr, mDepthStencil.GetAddressOf())
				));
			assert(SUCCEEDED(
				mDevice->CreateDepthStencilView(mDepthStencil.Get(), nullptr, mDSV.GetAddressOf())
				));
		}

			
		DWORD shaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
		shaderFlags |= D3DCOMPILE_DEBUG;
		shaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;

		//vertex shader
		{
			ID3DBlob* errorBlob = nullptr;
			D3DCompileFromFile(L"..\\SHADER\\Triangle_VS.hlsl", nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE
				, "main", "vs_5_0", shaderFlags, 0, &KRenderer::vsBlob, &errorBlob);

			mDevice->CreateVertexShader(KRenderer::vsBlob->GetBufferPointer()
				, KRenderer::vsBlob->GetBufferSize(), nullptr, &KRenderer::vsShader);
		}

		//pixel shader
		{
			ID3DBlob* errorBlob = nullptr;
			D3DCompileFromFile(L"..\\SHADER\\Triangle_PS.hlsl", nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE
				, "main", "ps_5_0", shaderFlags, 0, &KRenderer::psBlob, &errorBlob);

			mDevice->CreatePixelShader(KRenderer::psBlob->GetBufferPointer()
				, KRenderer::psBlob->GetBufferSize(), nullptr, &KRenderer::psShader);
		}

		D3D11_INPUT_ELEMENT_DESC inputLayoutDesces[2] = {};

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

		mDevice->CreateInputLayout(inputLayoutDesces, 2
			, KRenderer::vsBlob->GetBufferPointer()
			, KRenderer::vsBlob->GetBufferSize()
			, &KRenderer::inputLayouts);

		D3D11_BUFFER_DESC bufferDesc = {};

		bufferDesc.ByteWidth = sizeof(KRenderer::Vertex) * 3;
		bufferDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
		bufferDesc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
		bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;
		
		//xyz
		//rgba
		KRenderer::vertexes[0].pos = KMath::Vector3(0.f, 0.5f, 0.0f);
		KRenderer::vertexes[0].color = KMath::Vector4(0.0f, 1.0f, 0.0f, 1.0f);

		KRenderer::vertexes[1].pos = KMath::Vector3(0.5f, -0.5f, 0.0f);
		KRenderer::vertexes[1].color = KMath::Vector4(1.0f, 0.0f, 0.0f, 1.0f);

		KRenderer::vertexes[2].pos = KMath::Vector3(-0.5f, -0.5f, 0.0f);
		KRenderer::vertexes[2].color = KMath::Vector4(0.0f, 0.0f, 1.0f, 1.0f);

		D3D11_SUBRESOURCE_DATA sub = { KRenderer::vertexes };
		//sub.pSysMem = renderer::vertexes;

		mDevice->CreateBuffer(&bufferDesc, &sub, &KRenderer::vertexBuffer);
	}

	void GraphicDevice_DX11::Draw()
	{
		FLOAT backgroundColor[4] = {1.f, 0.f, 1.f, 1.f};
		mDeviceContext->ClearRenderTargetView(mRTV.Get(), backgroundColor);

		mDeviceContext->ClearDepthStencilView(mDSV.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.f, 0);

		D3D11_VIEWPORT viewPort =
		{
			0, 0, (FLOAT)application.GetViewSize().width, (FLOAT)application.GetViewSize().height,
			0.0f, 1.0f
		};
		mDeviceContext->RSSetViewports(1, &viewPort);
		mDeviceContext->OMSetRenderTargets(1, mRTV.GetAddressOf(), mDSV.Get());

		mDeviceContext->IASetInputLayout(KRenderer::inputLayouts);
		mDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		UINT vertexSize = sizeof(KRenderer::Vertex);
		UINT offset = 0;
		mDeviceContext->IASetVertexBuffers(0, 1, &KRenderer::vertexBuffer, &vertexSize, &offset);

		mDeviceContext->VSSetShader(KRenderer::vsShader, 0, 0);
		mDeviceContext->PSSetShader(KRenderer::psShader, 0, 0);

		mDeviceContext->Draw(3, 0);

		mSwapChain->Present(1, 0);
	}
}
