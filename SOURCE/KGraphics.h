#pragma once
#include "CommonInclude.h"

namespace KGraphics
{
	struct Vertex
	{
		KMath::Vector3 pos;
		KMath::Vector4 color;
		KMath::Vector2 uv;
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

		End
	};

	enum class eCBType
	{
		Transform,

		End
	};

	enum class eSamplerType
	{
		Point,
		Linear,
		Anisotropic,
		PostProcess,

		End
	};

	enum class eRenderingMode
	{
		Opaque,
		CutOut,
		Transparent,
		PostProcess,

		End
	};

	enum class eTextureType
	{
		Albedo,
		Normal,
		Specular,
		Smoothness,
		Metallic,

		End
	};

	struct GPUBuffer
	{
		Microsoft::WRL::ComPtr<ID3D11Buffer> buffer;
		D3D11_BUFFER_DESC desc;

		GPUBuffer() = default;
		virtual ~GPUBuffer() = default;
	};
}