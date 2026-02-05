#pragma once
#include "KCamera.h"
#include "KGraphicDevice_DX11.h"

namespace KRenderer
{
	extern KEngine::Camera* mainCamera;

	struct Vertex
	{
		KMath::Vector3 pos;
		KMath::Vector4 color;
	};

	extern Vertex											vertexes[3];
	extern Microsoft::WRL::ComPtr<ID3D11Buffer>				vertexBuffer;

	extern std::vector<UINT>								indices;
	extern Microsoft::WRL::ComPtr<ID3D11Buffer>				indexBuffer;

	extern Microsoft::WRL::ComPtr<ID3D11Buffer>				constantBuffer;

	extern Microsoft::WRL::ComPtr<ID3DBlob>					vsBlob;
	extern Microsoft::WRL::ComPtr<ID3D11VertexShader>		vsShader;

	extern Microsoft::WRL::ComPtr<ID3DBlob>					psBlob;
	extern Microsoft::WRL::ComPtr<ID3D11PixelShader>		psShader;

	extern Microsoft::WRL::ComPtr<ID3D11InputLayout>		inputLayouts;

	void Initialize();
	void Release();
}