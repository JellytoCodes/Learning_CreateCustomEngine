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

	/*
	[Init: 렌더 시스템 부팅(1회)]
	목적:
	- 한 프레임을 그리기 위해 필요한 "고정 리소스(디바이스/스왑체인/뷰/셰이더/버퍼)"를 생성한다.
	- D3D11은 상태 기반(Stateful) 파이프라인이므로, Draw에서 쓰일 대부분의 리소스는 여기서 준비해둔다.

	생성/설정 순서(의존성 때문에 중요):
	1) KRenderer::Initialize()
	   - 렌더러 레벨 전역/공용 리소스 초기화(정점/인덱스/상수버퍼 등 보관 영역 포함 가능)

	2) CreateDevice()
	   - ID3D11Device: GPU 리소스 생성 공장
	   - ID3D11DeviceContext: 파이프라인 상태 설정 + Draw 호출(커맨드 발행자)

	3) CreateSwapChain()
	   - DXGI SwapChain: 백버퍼(프레젠테이션용 텍스처들) + Present 메커니즘

	4) GetBuffer(BackBuffer) -> CreateRenderTargetView()
	   - SwapChain의 0번 백버퍼(Texture2D) 획득
	   - RTV(Render Target View) 생성: OM 단계에 “색 출력 대상”으로 연결하는 View

	5) CreateVertexShader / CreatePixelShader
	   - HLSL 컴파일(Blob) -> 셰이더 객체 생성
	   - VS Blob은 InputLayout 생성 시 입력 시그니처 검증에 필요

	6) CreateInputLayout()
	   - IA 단계에서 VertexBuffer의 raw bytes를 POSITION/COLOR 같은 시맨틱으로 해석하는 규칙 정의

	7) CreateDepthStencilView()
	   - 깊이/스텐실용 텍스처 생성 + DSV 생성
	   - OM 단계에서 깊이 테스트/기록 대상

	8) CreateVertexBuffer / CreateIndexBuffer / CreateConstantBuffer
	   - IA가 읽을 VB/IB, 셰이더가 읽을 CB 준비
	*/
	void GraphicDevice_DX11::Initialize()
	{
		KRenderer::Initialize();

		// [Init] D3D11 Device + Immediate Context 생성
		CreateDevice();

		// [Init] SwapChain 생성(백버퍼 포함)
		CreateSwapChain();

		// [Init] SwapChain 백버퍼(Texture2D) 획득
		GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)mRenderTarget.GetAddressOf());

		// [Init] 백버퍼를 RTV로 래핑(OM 단계 출력 타겟)
		CreateRenderTargetView();

		// [Init] 셰이더 컴파일 + 생성(VS/PS)
		CreateVertexShader(L"Triangle_VS.hlsl");
		CreatePixelShader(L"Triangle_PS.hlsl");

		// [Init] 입력 레이아웃(IA 단계: 정점 포맷 해석 규칙)
		CreateInputLayout();

		// [Init] 깊이/스텐실 버퍼 + DSV(OM 단계 depth/stencil 타겟)
		CreateDepthStencilView();

		// [Init] 기하 데이터(VB/IB) + 셰이더 상수(CB)
		CreateVertexBuffer();
		CreateIndexBuffer();
		CreateConstantBuffer();
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

	프레임 내부 순서:
	1) Clear (RTV/DSV)
	2) Viewport 설정(RS)
	3) OMSetRenderTargets (OM)
	4) 리소스 바인딩(CB/VB/IB/InputLayout/Shader)
	5) DrawIndexed
	6) Present
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
		BindConstantBuffer(KGraphics::eShaderStage::VS, KGraphics::eCBType::Transform, KRenderer::constantBuffer.Get());

		// [Frame] IA 단계: InputLayout + Primitive Topology 설정
		mDeviceContext->IASetInputLayout(KRenderer::inputLayouts.Get());
		mDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		// [Frame] IA 단계: Vertex Buffer 바인딩(스트라이드/오프셋 중요)
		UINT vertexSize = sizeof(KRenderer::Vertex);
		UINT offset = 0;

		mDeviceContext->IASetVertexBuffers(0, 1, KRenderer::vertexBuffer.GetAddressOf(), &vertexSize, &offset);

		// [Frame] IA 단계: Index Buffer 바인딩(여기서는 R32_UINT)
		mDeviceContext->IASetIndexBuffer(KRenderer::indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);

		// [Frame] VS/PS 단계: 셰이더 바인딩
		mDeviceContext->VSSetShader(KRenderer::vsShader.Get(), 0, 0);
		mDeviceContext->PSSetShader(KRenderer::psShader.Get(), 0, 0);

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
	[Init: Vertex Shader(VS) 컴파일 + 생성]
	목적:
	- HLSL 파일을 컴파일해서 VS 바이트코드(Blob)를 만들고,
	  그 바이트코드로 ID3D11VertexShader 객체를 생성한다.

	왜 Blob(vsBlob)을 저장하나:
	- InputLayout 생성 시 VS의 입력 시그니처(semantic/format)를 기준으로
	  앱이 지정한 InputElementDesc가 호환되는지 검증해야 한다.
	- 그래서 CreateInputLayout에서 vsBlob가 필수로 사용된다.

	compile 설정:
	- vs_5_0 : Shader Model 5.0 Vertex Shader
	- DEBUG/SKIP_OPTIMIZATION: 디버깅 편의(성능 희생)
	*/
	void GraphicDevice_DX11::CreateVertexShader(const std::wstring& fileName)
	{
		DWORD shaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
		shaderFlags |= D3DCOMPILE_DEBUG;
		shaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;

		ID3DBlob* errorBlob = nullptr;
		const std::wstring shaderFilePath = L"..\\SHADER\\";
		HRESULT hr = D3DCompileFromFile(
		(shaderFilePath + fileName).c_str(), 
		nullptr, 
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		"main",
		"vs_5_0",
		shaderFlags,
		0,
		KRenderer::vsBlob.GetAddressOf(),
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
			mDevice->CreateVertexShader(
			(KRenderer::vsBlob)->GetBufferPointer(), 
			(KRenderer::vsBlob)->GetBufferSize(), 
			nullptr, 
			KRenderer::vsShader.GetAddressOf())
		));
	}

	/*
	[Init: Pixel Shader(PS) 컴파일 + 생성]
	목적:
	- HLSL 파일을 컴파일해서 PS 바이트코드(Blob)를 만들고,
	  그 바이트코드로 ID3D11PixelShader 객체를 생성한다.

	PS 역할:
	- 래스터라이즈된 픽셀(프래그먼트)마다 최종 색/출력 값을 계산한다.
	- 결과는 OM 단계에서 RTV에 기록된다.

	compile 설정:
	- ps_5_0 : Shader Model 5.0 Pixel Shader
	*/
	void GraphicDevice_DX11::CreatePixelShader(const std::wstring& fileName)
	{
		DWORD shaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
		shaderFlags |= D3DCOMPILE_DEBUG;
		shaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;

		ID3DBlob* errorBlob = nullptr;
		const std::wstring shaderFilePath = L"..\\SHADER\\";
		HRESULT hr = D3DCompileFromFile(
		(shaderFilePath + fileName).c_str(), 
		nullptr, 
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		"main",
		"ps_5_0",
		shaderFlags,
		0,
		KRenderer::psBlob.GetAddressOf(),
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
			mDevice->CreatePixelShader(
			KRenderer::psBlob->GetBufferPointer(), 
			KRenderer::psBlob->GetBufferSize(),
			nullptr,
			KRenderer::psShader.GetAddressOf())
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

		mDevice->CreateInputLayout(
		inputLayoutDesces, 
		2,
		KRenderer::vsBlob->GetBufferPointer(),
		KRenderer::vsBlob->GetBufferSize(),
		KRenderer::inputLayouts.GetAddressOf());
	}

	/*
	[Init: Vertex Buffer 생성]
	목적:
	- 정점 데이터를 GPU 리소스로 생성하여 IA 단계 입력으로 사용할 준비를 한다.

	설정 의미:
	- BindFlags=VERTEX_BUFFER: IA가 정점 스트림으로 읽는다.
	- Usage=DYNAMIC + CPUAccess=WRITE:
	  CPU가 Map/Unmap으로 내용 갱신 가능한 버퍼(수시 업데이트 목적).

	초기 데이터:
	- D3D11_SUBRESOURCE_DATA로 초기 정점 데이터(KRenderer::vertexes) 업로드.
	*/
	void GraphicDevice_DX11::CreateVertexBuffer()
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));

		desc.ByteWidth = sizeof(KRenderer::Vertex) * 3;
		desc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
		desc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;

		D3D11_SUBRESOURCE_DATA data = { KRenderer::vertexes };

		assert(SUCCEEDED(
			mDevice->CreateBuffer(&desc, &data, KRenderer::vertexBuffer.GetAddressOf())
		));
	}

	/*
	[Init: Index Buffer 생성]
	목적:
	- 인덱스 데이터를 GPU 리소스로 생성하여 DrawIndexed에서 사용할 준비를 한다.

	설정 의미:
	- BindFlags=INDEX_BUFFER: IA가 인덱스 스트림으로 읽는다.
	- Usage=DEFAULT: 보통 한 번 업로드 후 잘 안 바꾸는 정적 데이터에 적합.

	파이프라인 소비:
	- IASetIndexBuffer로 바인딩
	- DrawIndexed의 indexCount만큼 이 버퍼를 읽어 정점 조립을 수행
	*/
	void GraphicDevice_DX11::CreateIndexBuffer()
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));

		desc.ByteWidth = sizeof(UINT) * KRenderer::indices.size();
		desc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_INDEX_BUFFER;
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA data;
		ZeroMemory(&data, sizeof(D3D11_SUBRESOURCE_DATA));

		data.pSysMem = KRenderer::indices.data();

		assert(SUCCEEDED(
			mDevice->CreateBuffer(&desc, &data, KRenderer::indexBuffer.GetAddressOf())
		));
	}

	/*
	[Init: Constant Buffer 생성]
	목적:
	- 셰이더에서 참조하는 작은 상수 데이터 묶음을 담는 버퍼 생성.
	- 일반적으로 Transform(행렬), 오브젝트/카메라 파라미터, 시간값 등을 넣는다.

	설정 의미:
	- BindFlags=CONSTANT_BUFFER: b# 슬롯에 바인딩 가능
	- Usage=DYNAMIC + CPUAccess=WRITE: CPU가 Map으로 값 갱신 가능
	- ByteWidth: 16바이트 배수 권장(정렬 규칙). Vector4는 16B.

	현재 데이터 의도:
	- pos(Vector4)를 넣어 VS에서 위치 오프셋/변환 등에 사용하려는 형태.
	*/
	void GraphicDevice_DX11::CreateConstantBuffer()
	{
		D3D11_BUFFER_DESC desc = {};
		desc.ByteWidth = sizeof(KMath::Vector4); // constant buffer 
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		desc.Usage = D3D11_USAGE_DYNAMIC;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		KMath::Vector4 pos(-0.5f, 0.0f, 0.0f, 1.0f);
		D3D11_SUBRESOURCE_DATA data = {};
		data.pSysMem = &pos;

		assert(SUCCEEDED(
			mDevice->CreateBuffer(&desc, &data, KRenderer::constantBuffer.GetAddressOf())
		));
	}

	/*
	[Frame/Init 공용: Constant Buffer 바인딩 유틸]
	목적:
	- 특정 셰이더 스테이지(VS/PS/...)의 constant buffer 슬롯(b#)에 버퍼를 연결한다.

	핵심 규칙:
	- slot = (UINT)type
	  => eCBType enum 값이 HLSL의 register(b#) 인덱스와 1:1로 대응되어야 한다.
	     (예: Transform = 0이면 HLSL은 register(b0))

	stage 의미:
	- VS/PS/... 별로 각 단계에만 바인딩 가능
	- All은 모든 단계에 같은 CB를 동시에 바인딩(공용 파라미터용)
	*/
	void GraphicDevice_DX11::BindConstantBuffer(KGraphics::eShaderStage stage, KGraphics::eCBType type, ID3D11Buffer* buffer)
	{
		UINT slot = (UINT)type;
		switch (stage)
		{
		case KGraphics::eShaderStage::VS:
			mDeviceContext->VSSetConstantBuffers(slot, 1, &buffer);
			break;
		case KGraphics::eShaderStage::HS:
			mDeviceContext->HSSetConstantBuffers(slot, 1, &buffer);
			break;
		case KGraphics::eShaderStage::DS:
			mDeviceContext->DSSetConstantBuffers(slot, 1, &buffer);
			break;
		case KGraphics::eShaderStage::GS:
			mDeviceContext->GSSetConstantBuffers(slot, 1, &buffer);
			break;
		case KGraphics::eShaderStage::PS:
			mDeviceContext->PSSetConstantBuffers(slot, 1, &buffer);
			break;
		case KGraphics::eShaderStage::CS:
			mDeviceContext->CSSetConstantBuffers(slot, 1, &buffer);
			break;
		case KGraphics::eShaderStage::All:
			mDeviceContext->VSSetConstantBuffers(slot, 1, &buffer);
			mDeviceContext->HSSetConstantBuffers(slot, 1, &buffer);
			mDeviceContext->DSSetConstantBuffers(slot, 1, &buffer);
			mDeviceContext->GSSetConstantBuffers(slot, 1, &buffer);
			mDeviceContext->PSSetConstantBuffers(slot, 1, &buffer);
			mDeviceContext->CSSetConstantBuffers(slot, 1, &buffer);
			break;
		default:
			break;
		}
	}
}
