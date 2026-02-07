#include "KRenderer.h"

#include "KResources.h"
#include "KShader.h"

namespace KRenderer
{
    KEngine::Camera* KRenderer::mainCamera = nullptr;

	std::vector<KGraphics::Vertex>		KRenderer::vertexes;
	KEngine::VertexBuffer				KRenderer::vertexBuffer;

	std::vector<UINT>					KRenderer::indices;
	KEngine::IndexBuffer				KRenderer::indexBuffer;

	KEngine::ConstantBuffer				KRenderer::constantBuffers[(UINT)KGraphics::eCBType::End] = {};

	Microsoft::WRL::ComPtr<ID3D11InputLayout>		KRenderer::inputLayouts;

	void LoadTriangleMesh()
	{
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
	}

	void LoadMeshes()
	{
		LoadTriangleMesh();
	}

	void LoadShaders()
	{
		KEngine::Resources::Load<KEngine::Shader>(L"TriangleShader", L"..\\SHADER\\Triangle");
	}

	void Initialize()
	{
		LoadMeshes();
		LoadShaders();
		KRenderer::constantBuffers[(UINT)KGraphics::eCBType::Transform].Create(KGraphics::eCBType::Transform, sizeof(KMath::Vector4));
	}

	void Release()
	{

	}
}
