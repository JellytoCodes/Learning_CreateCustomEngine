#include "KMesh.h"

namespace KEngine
{
	Mesh::Mesh()
		: Super(eResourceType::Mesh)
	{

	}

	Mesh::~Mesh()
	{

	}

	HRESULT Mesh::Save(const std::wstring& path)
	{
		return S_OK;
	}

	HRESULT Mesh::Load(const std::wstring& path)
	{
		return S_OK;
	}

	void Mesh::CreateVB(const std::vector<KGraphics::Vertex>& vertices)
	{
		mData.vertices = vertices;
		mVertexBuffer.Create(vertices);
	}

	void Mesh::CreateIB(const std::vector<UINT>& indices)
	{
		mData.indices = indices;
		mIndexBuffer.Create(indices);
	}

	void Mesh::Bind()
	{
		// [Frame] IA 단계: Vertex Buffer 바인딩(스트라이드/오프셋 중요)
		mVertexBuffer.Bind();

		// [Frame] IA 단계: Index Buffer 바인딩(여기서는 R32_UINT)
		mIndexBuffer.Bind();

		GraphicDevice_DX11::getInstance().GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}
}
