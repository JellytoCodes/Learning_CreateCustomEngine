#pragma once
#include "CommonInclude.h"

namespace KGraphics
{
	struct Vertex
	{
		KMath::Vector3 pos;
		KMath::Vector4 color;
	};
	enum class eShaderStage
	{
		VS,		// Vertex Shader
		HS,		// Hull Shader
		DS,		// Domain Shader
		GS,		// Geometry Shader
		PS,		// Pixel Shader
		CS,		// Compute Shader
		All,
		End,
	};

	enum class eCBType
	{
		Transform,
		End,
	};

	struct GPUBuffer
	{
		Microsoft::WRL::ComPtr<ID3D11Buffer> buffer;
		D3D11_BUFFER_DESC desc;

		GPUBuffer() = default;
		virtual ~GPUBuffer() = default;
	};
}