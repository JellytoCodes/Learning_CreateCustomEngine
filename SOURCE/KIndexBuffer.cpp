#include "KIndexBuffer.h"

namespace KEngine
{
	IndexBuffer::IndexBuffer()
	{

	}

	IndexBuffer::~IndexBuffer()
	{

	}

	void IndexBuffer::Create(const std::vector<UINT>& indices)
	{
		mIndexCount = indices.size();

		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));

		desc.ByteWidth = sizeof(UINT) * indices.size();
		desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA data;
		ZeroMemory(&data, sizeof(D3D11_SUBRESOURCE_DATA));

		data.pSysMem = indices.data();

		assert(SUCCEEDED(
			GraphicDevice_DX11::getInstance().GetDevice()->CreateBuffer(&desc, &data, buffer.GetAddressOf())
		));
	}

	void IndexBuffer::Bind()
	{
		GraphicDevice_DX11::getInstance().GetDeviceContext()->IASetIndexBuffer(buffer.Get(), DXGI_FORMAT_R32_UINT, 0);
	}
}
