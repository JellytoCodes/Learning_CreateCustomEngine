#include "KRenderer.h"

#include "KMaterial.h"
#include "KResources.h"
#include "KShader.h"

namespace KRenderer
{
    KEngine::Camera*							KRenderer::mainCamera = nullptr;

	std::unique_ptr<KEngine::Mesh>				KRenderer::mesh;

	KEngine::ConstantBuffer						KRenderer::constantBuffers[(UINT)KGraphics::eCBType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11InputLayout>	KRenderer::inputLayouts;

	Microsoft::WRL::ComPtr<ID3D11SamplerState>	samplerStates[(UINT)KGraphics::eSamplerType::End] = {};

	void LoadStates()
	{
		D3D11_SAMPLER_DESC samplerDesc = {};
		samplerDesc.Filter = D3D11_FILTER::D3D11_FILTER_ANISOTROPIC;
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.ComparisonFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_NEVER;
		samplerDesc.MinLOD = 0;
		samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;
		KEngine::GraphicDevice_DX11::getInstance().GetDevice()->CreateSamplerState(&samplerDesc, samplerStates[(UINT)KGraphics::eSamplerType::Anisotropic].GetAddressOf());

		ZeroMemory(&samplerDesc, sizeof(samplerDesc));
		samplerDesc.Filter = D3D11_FILTER::D3D11_FILTER_MIN_MAG_MIP_POINT;
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.ComparisonFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_NEVER;
		samplerDesc.MinLOD = 0;
		samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;
		KEngine::GraphicDevice_DX11::getInstance().GetDevice()->CreateSamplerState(&samplerDesc, samplerStates[(UINT)KGraphics::eSamplerType::Point].GetAddressOf());

		ZeroMemory(&samplerDesc, sizeof(samplerDesc));
		samplerDesc.Filter = D3D11_FILTER::D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.ComparisonFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_NEVER;
		samplerDesc.MinLOD = 0;
		samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;
		KEngine::GraphicDevice_DX11::getInstance().GetDevice()->CreateSamplerState(&samplerDesc, samplerStates[(UINT)KGraphics::eSamplerType::Linear].GetAddressOf());

		ZeroMemory(&samplerDesc, sizeof(samplerDesc));
		samplerDesc.Filter = D3D11_FILTER::D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_CLAMP;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_CLAMP;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_CLAMP;
		samplerDesc.ComparisonFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_NEVER;
		samplerDesc.MinLOD = 0;
		samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;
		KEngine::GraphicDevice_DX11::getInstance().GetDevice()->CreateSamplerState(&samplerDesc, samplerStates[(UINT)KGraphics::eSamplerType::PostProcess].GetAddressOf());

		KEngine::GraphicDevice_DX11::getInstance().BindSamplers(
			(UINT)KGraphics::eSamplerType::Point, 1, samplerStates[(UINT)KGraphics::eSamplerType::Point].GetAddressOf());
		KEngine::GraphicDevice_DX11::getInstance().BindSamplers(
			(UINT)KGraphics::eSamplerType::Linear, 1, samplerStates[(UINT)KGraphics::eSamplerType::Linear].GetAddressOf());
		KEngine::GraphicDevice_DX11::getInstance().BindSamplers(
			(UINT)KGraphics::eSamplerType::Anisotropic, 1, samplerStates[(UINT)KGraphics::eSamplerType::Anisotropic].GetAddressOf());
		KEngine::GraphicDevice_DX11::getInstance().BindSamplers(
			(UINT)KGraphics::eSamplerType::PostProcess, 1, samplerStates[(UINT)KGraphics::eSamplerType::PostProcess].GetAddressOf());
	}

	void LoadTriangleMesh()
	{
		mesh = std::make_unique<KEngine::Mesh>();

		std::vector<KGraphics::Vertex>	vertexes;
		std::vector<UINT>				indices;

		vertexes.resize(3);
		vertexes[0].pos = KMath::Vector3(0.f, 0.5f, 0.0f);
		vertexes[0].color = KMath::Vector4(0.0f, 1.0f, 0.0f, 1.0f);

		vertexes[1].pos = KMath::Vector3(0.5f, -0.5f, 0.0f);
		vertexes[1].color = KMath::Vector4(1.0f, 0.0f, 0.0f, 1.0f);

		vertexes[2].pos = KMath::Vector3(-0.5f, -0.5f, 0.0f);
		vertexes[2].color = KMath::Vector4(0.0f, 0.0f, 1.0f, 1.0f);

		indices.push_back(0);
		indices.push_back(1);
		indices.push_back(2);

		mesh->CreateVB(vertexes);
		mesh->CreateIB(indices);

		KEngine::Resources::Insert(L"TriangleMesh", std::move(mesh));
	}
	void LoadRectMesh()
	{
		mesh = std::make_unique<KEngine::Mesh>();

		std::vector<KGraphics::Vertex> vertexes = {};
		std::vector<UINT> indices = {};

		vertexes.resize(4);
		vertexes[0].pos = KMath::Vector3(-0.5f, 0.5f, 0.0f);
		vertexes[0].color = KMath::Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		vertexes[0].uv = KMath::Vector2(0.0f, 0.0f);

		vertexes[1].pos = KMath::Vector3(0.5f, 0.5f, 0.0f);
		vertexes[1].color = KMath::Vector4(1.0f, 0.0f, 0.0f, 1.0f);
		vertexes[1].uv = KMath::Vector2(1.0f, 0.0f);

		vertexes[2].pos = KMath::Vector3(0.5f, -0.5f, 0.0f);
		vertexes[2].color = KMath::Vector4(0.0f, 0.0f, 1.0f, 1.0f);
		vertexes[2].uv = KMath::Vector2(1.0f, 1.0f);

		vertexes[3].pos = KMath::Vector3(-0.5f, -0.5f, 0.0f);
		vertexes[3].color = KMath::Vector4(0.0f, 0.0f, 1.0f, 1.0f);
		vertexes[3].uv = KMath::Vector2(0.0f, 1.0f);
		
		indices.push_back(0);
		indices.push_back(1);
		indices.push_back(2);

		indices.push_back(0);
		indices.push_back(2);
		indices.push_back(3);

		mesh->CreateVB(vertexes);
		mesh->CreateIB(indices);

		KEngine::Resources::Insert(L"RectMesh", std::move(mesh));
	}

	void LoadMeshes()
	{
		LoadTriangleMesh();
		LoadRectMesh();
	}

	void LoadShaders()
	{
		KEngine::Resources::Load<KEngine::Shader>(L"TriangleShader", L"..\\SHADER\\Triangle");
		KEngine::Resources::Load<KEngine::Shader>(L"SpriteShader",L"..\\SHADER\\Sprite");
	}

	void LoadMeterials()
	{
		std::unique_ptr<KEngine::Material> spriteMaterial = std::make_unique<KEngine::Material>();
		KEngine::Material* rawMaterial = spriteMaterial.get();

		KEngine::Resources::Insert(L"SpriteMaterial", std::move(spriteMaterial));

		rawMaterial->SetShader(KEngine::Resources::Find<KEngine::Shader>(L"SpriteShader"));
		//ya::Resources::Load<graphics::Material>(L"SpriteMaterial", L"..\\Materials\\SpriteMaterial")
	}

	void Initialize()
	{
		LoadMeshes();
		LoadShaders();
		LoadMeterials();
		KRenderer::constantBuffers[(UINT)KGraphics::eCBType::Transform].Create(KGraphics::eCBType::Transform, sizeof(KMath::Vector4));
	}

	void Release()
	{

	}
}
