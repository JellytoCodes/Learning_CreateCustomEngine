#pragma once

#include "KCamera.h"
#include "KConstantBuffer.h"
#include "KGraphicDevice_DX11.h"
#include "KIndexBuffer.h"
#include "KVertexBuffer.h"

namespace KRenderer
{
	extern KEngine::Camera* mainCamera;

	extern std::vector<KGraphics::Vertex>	vertexes;
	extern KEngine::VertexBuffer			vertexBuffer;

	extern std::vector<UINT>				indices;
	extern KEngine::IndexBuffer				indexBuffer;
	extern KEngine::ConstantBuffer			constantBuffers[(UINT)KGraphics::eCBType::End];

	extern Microsoft::WRL::ComPtr<ID3D11InputLayout>		inputLayouts;

	void Initialize();
	void Release();
}
