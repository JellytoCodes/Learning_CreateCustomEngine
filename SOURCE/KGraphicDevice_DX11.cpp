#include "KGraphicDevice_DX11.h"
#include "KApplication.h"
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
		// [Init] D3D11 Device + Immediate Context 생성
		CreateDevice();
		KRenderer::Initialize();

		// [Init] SwapChain 생성(백버퍼 포함)
		CreateSwapChain();

		// [Init] SwapChain 백버퍼(Texture2D) 획득
		GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)mRenderTarget.GetAddressOf());

		// [Init] 백버퍼를 RTV로 래핑(OM 단계 출력 타겟)
		CreateRenderTargetView();

		// [Init] 셰이더 컴파일 + 생성(VS/PS)

		// [Init] 입력 레이아웃(IA 단계: 정점 포맷 해석 규칙)
		CreateInputLayout();

		// [Init] 깊이/스텐실 버퍼 + DSV(OM 단계 depth/stencil 타겟)
		CreateDepthStencilView();
	}

	/*
	[Frame: 매 프레임 렌더 커맨드 구성 + 실행]
	목적:
	- 이번 프레임에 사용할 렌더 타겟/뷰포트/파이프라인 상태/리소스 바인딩을 설정하고 Draw 호출을 수행한다.

	D3D11 파이프라인 소비 흐름(큰 그림):
	IA(Input Assembler) : VB/IB + InputLayout + Topology로 정점 조립 재료 준비
	VS(Vertex Shader)   : 정점 단위 처리(좌표 변환/출력 시맨틱 생성)
	RS(Rasterizer)      : Viewport/래스터라이즈(삼각형을 픽셀 후보로 분해)
	PS(Pixel Shader)    : 픽셀 단위 색/라이팅 계산
	OM(Output Merger)   : Depth/Stencil 테스트 + RTV에 최종 색 기록
	Present(DXGI)       : 백버퍼를 화면으로 표시
	*/
	void GraphicDevice_DX11::Draw()
	{
		// [Frame] RTV(색 버퍼) 초기화
		FLOAT backgroundColor[4] = {0.2f, 0.2f, 0.2f, 1.f};
		mDeviceContext->ClearRenderTargetView(mRTV.Get(), backgroundColor);

		// [Frame] DSV(깊이/스텐실 버퍼) 초기화
		// - depth=1.0f : 가장 먼 값으로 초기화(일반적인 depth 비교 규칙에서 “비어 있음” 의미)
		// - stencil=0  : 스텐실 초기값
		mDeviceContext->ClearDepthStencilView(mDSV.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.f, 0);

		// [Frame] RS 단계: Viewport 설정(NDC -> 화면 픽셀 매핑)
		D3D11_VIEWPORT viewPort =
		{
			0, 0, (FLOAT)application.GetViewSize().width, (FLOAT)application.GetViewSize().height,
			0.0f, 1.0f
		};
		mDeviceContext->RSSetViewports(1, &viewPort);

		// [Frame] OM 단계: 출력 타겟 지정(RTV + DSV)
		mDeviceContext->OMSetRenderTargets(1, mRTV.GetAddressOf(), mDSV.Get());

		// [Frame] VS 단계: Constant Buffer 바인딩(Transform 슬롯)
		// - HLSL의 register(b#)와 eCBType enum 값(slot)이 일치해야 함
		//BindConstantBuffer(KGraphics::eShaderStage::VS, KGraphics::eCBType::Transform, KRenderer::constantBuffer.Get());

		// [Frame] IA 단계: InputLayout + Primitive Topology 설정
		mDeviceContext->IASetInputLayout(KRenderer::inputLayouts.Get());

		KRenderer::mesh->Bind();

		KMath::Vector4 pos(-0.5f, 0.0f, 0.0f, 1.0f);
		KRenderer::constantBuffers[(UINT)KGraphics::eCBType::Transform].SetData(&pos);
		KRenderer::constantBuffers[(UINT)KGraphics::eCBType::Transform].BindConstantBuffer(KGraphics::eShaderStage::VS);

		// [Frame] VS/PS 단계: 셰이더 바인딩
		Shader* shader = Resources::Find<Shader>(L"TriangleShader");
		mDeviceContext->VSSetShader(shader->GetVertexShader(), 0, 0);
		mDeviceContext->PSSetShader(shader->GetPixelShader(), 0, 0);

		// [Frame] Draw 실행: Index Buffer 기준으로 기하를 조립해서 렌더링 수행
		mDeviceContext->DrawIndexed(KRenderer::indices.size(),0, 0);

		// [Frame] Present: SwapChain 백버퍼를 화면에 표시
		// - Present(1,0): VSync(동기) 기반 프레젠테이션
		mSwapChain->Present(1, 0);
	}

	/*
	[Init: D3D11 Device + Immediate Context 생성]
	생성물:
	- mDevice        : 리소스 생성 공장(버퍼/텍스처/뷰/셰이더 생성 API)
	- mDeviceContext : 파이프라인 상태 설정 + Draw 호출(커맨드 발행)

	중요 옵션:
	- D3D11_CREATE_DEVICE_BGRA_SUPPORT : BGRA 포맷/interop(주로 DXGI/D2D)
	- D3D11_CREATE_DEVICE_DEBUG        : 디버그 레이어(런타임 검증/오류 출력)
	*/
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

	/*
	[Init: SwapChain 생성(DXGI 프레젠테이션 구성)]
	생성물:
	- mSwapChain: 백버퍼 텍스처 집합 + Present() 메커니즘

	개념:
	- SwapChain은 “그릴 대상(백버퍼)”을 내부에 가지고 있고,
	  Present가 그 백버퍼를 화면(front)으로 내보낸다.

	구성 포인트:
	- BufferCount=2 : 더블 버퍼링
	- BufferUsage   : RENDER_TARGET_OUTPUT (백버퍼를 렌더 타겟으로 사용)
	- Format        : R8G8B8A8_UNORM (표준 8-bit RGBA)
	- SwapEffect    : DISCARD (Present 이후 백버퍼 내용 보존을 보장하지 않는 모델)

	DXGI 객체 그래프(왜 QueryInterface/GetParent를 타는가):
	- Device -> IDXGIDevice -> Adapter -> Factory -> CreateSwapChain
	  (어떤 GPU 어댑터/팩토리 컨텍스트에서 스왑체인을 만들지 명시)
	*/
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

	/*
	[Init: SwapChain 백버퍼 획득]
	목적:
	- SwapChain 내부의 N번째 버퍼(대개 0번 백버퍼)를 꺼내 Texture2D로 받는다.
	- 이 텍스처를 “직접” 파이프라인에 붙이지 않고, RTV(View)로 래핑해 OM에 연결한다.

	파라미터:
	- Buffer : 얻고 싶은 버퍼 인덱스
	- riid   : 요청할 COM 인터페이스 타입(여기서는 ID3D11Texture2D)
	- ppSurface: 결과 포인터
	*/
	void GraphicDevice_DX11::GetBuffer(UINT Buffer, const IID& riid, void** ppSurface)
	{
		assert(SUCCEEDED(
			mSwapChain->GetBuffer(Buffer, riid, ppSurface)
		));
	}

	/*
	[Init: Render Target View(RTV) 생성]
	목적:
	- BackBuffer Texture2D를 RTV로 감싼다.
	- RTV는 OM(Output Merger) 단계에서 "색 출력 대상"으로 사용된다.
	*/
	void GraphicDevice_DX11::CreateRenderTargetView()
	{
		// D3D11_RENDER_TARGET_VIEW_DESC desc;
		assert(SUCCEEDED(
			mDevice->CreateRenderTargetView(mRenderTarget.Get(), nullptr, mRTV.GetAddressOf())
		));
	}

	/*
	[Init: Depth/Stencil 텍스처 + DSV 생성]
	목적:
	- 깊이 테스트(Z)와 스텐실 테스트를 위한 전용 버퍼를 생성하고,
	  이를 DSV(View)로 만들어 OM 단계에 바인딩 가능하게 한다.

	중요:
	- SwapChain이 MSAA(멀티샘플)면 깊이버퍼도 동일 SampleDesc를 가져야 호환된다.
	  그래서 swapDesc.SampleDesc를 그대로 복사해 사용한다.
	*/
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

	/*
	[Init: Input Layout 생성(IA 단계 규칙)]
	목적:
	- VertexBuffer의 메모리 레이아웃을 HLSL 입력 시맨틱(POSITION/COLOR 등)과 매핑한다.

	현재 레이아웃 의미:
	- POSITION: float3, offset 0
	- COLOR   : float4, offset 12
	=> Vertex 구조가 [float3 position][float4 color] 순서로 연속 저장된다고 가정.

	주의:
	- SemanticName/Index는 VS 입력 파라미터 시맨틱과 정확히 일치해야 한다.
	- CreateInputLayout은 VS 바이트코드(vsBlob)를 받아 입력 시그니처 호환성을 검증한다.
	*/
	void GraphicDevice_DX11::CreateInputLayout()
	{
		DWORD shaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
		shaderFlags |= D3DCOMPILE_DEBUG;
		shaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;

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

		Shader* shader = Resources::Find<Shader>(L"TriangleShader");

		mDevice->CreateInputLayout(
		inputLayoutDesces, 
		2,
		shader->GetVSBlob()->GetBufferPointer(),
		shader->GetVSBlob()->GetBufferSize(),
		KRenderer::inputLayouts.GetAddressOf());
	}
}
