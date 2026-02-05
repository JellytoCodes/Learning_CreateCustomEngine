#include "KRenderer.h"

namespace KRenderer
{
    KEngine::Camera* KRenderer::mainCamera = nullptr;

	Vertex											KRenderer::vertexes[3] = {};
	Microsoft::WRL::ComPtr<ID3D11Buffer>			KRenderer::vertexBuffer;

	std::vector<UINT>								KRenderer::indices;
	Microsoft::WRL::ComPtr<ID3D11Buffer>			KRenderer::indexBuffer;

	Microsoft::WRL::ComPtr<ID3D11Buffer>			KRenderer::constantBuffer;

	Microsoft::WRL::ComPtr<ID3DBlob>				KRenderer::vsBlob;
	Microsoft::WRL::ComPtr<ID3D11VertexShader>		KRenderer::vsShader;

	Microsoft::WRL::ComPtr<ID3DBlob>				KRenderer::psBlob;
	Microsoft::WRL::ComPtr<ID3D11PixelShader>		KRenderer::psShader;

	Microsoft::WRL::ComPtr<ID3D11InputLayout>		KRenderer::inputLayouts;

	void LoadTriangleMesh()
	{
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

	void Initialize()
	{
		LoadMeshes();
	}

	void Release()
	{

	}
}