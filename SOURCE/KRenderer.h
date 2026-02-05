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

	extern Vertex vertexes[3];
	extern ID3D11Buffer* vertexBuffer;

	extern ID3DBlob* vsBlob;
	extern ID3D11VertexShader* vsShader;

	extern ID3DBlob* psBlob;
	extern ID3D11PixelShader* psShader;
	extern ID3D11InputLayout* inputLayouts;
}