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
		mVertexBuffer.Bind();
		mIndexBuffer.Bind();

		GraphicDevice_DX11::getInstance().GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}
}
