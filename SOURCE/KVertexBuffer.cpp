#include "KVertexBuffer.h"

namespace KEngine
{
	VertexBuffer::VertexBuffer()
	{

	}

	VertexBuffer::~VertexBuffer()
	{

	}

	void VertexBuffer::Create(const std::vector<KGraphics::Vertex>& vertexes)
	{
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));

		desc.ByteWidth = sizeof(KGraphics::Vertex) * vertexes.size();
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		desc.Usage = D3D11_USAGE_DYNAMIC;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		D3D11_SUBRESOURCE_DATA data = {};
		data.pSysMem = vertexes.data();

		assert(SUCCEEDED(
			GraphicDevice_DX11::getInstance().GetDevice()->CreateBuffer(&desc, &data, buffer.GetAddressOf())
		));
	}

	void VertexBuffer::Bind()
	{
		UINT offset = 0;
		UINT vertexSize = sizeof(KGraphics::Vertex);
		GraphicDevice_DX11::getInstance().GetDeviceContext()->IASetVertexBuffers(0, 1, buffer.GetAddressOf(), &vertexSize, &offset);
	}
}
