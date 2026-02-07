#include "KConstantBuffer.h"

namespace KEngine
{
	ConstantBuffer::ConstantBuffer()
	{
	}

	ConstantBuffer::~ConstantBuffer()
	{
	}

	void ConstantBuffer::Create(KGraphics::eCBType type, UINT size, void* data)
	{
		mSize = size;
		mType = type;

		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		desc.ByteWidth = size;
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		desc.Usage = D3D11_USAGE_DYNAMIC;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		D3D11_SUBRESOURCE_DATA sub = {};
		sub.pSysMem = data;

		assert(SUCCEEDED(
			GraphicDevice_DX11::getInstance().GetDevice()->CreateBuffer(&desc, data == NULL ? nullptr : &sub, buffer.GetAddressOf())
		));
	}

	void ConstantBuffer::SetData(void* data)
	{
		D3D11_MAPPED_SUBRESOURCE sub = {};
		GraphicDevice_DX11::getInstance().GetDeviceContext()->Map(buffer.Get(), 0, D3D11_MAP::D3D11_MAP_WRITE_DISCARD, 0, &sub);
		memcpy(sub.pData, data, mSize);
		GraphicDevice_DX11::getInstance().GetDeviceContext()->Unmap(buffer.Get(), 0);
	}

	void ConstantBuffer::BindConstantBuffer(KGraphics::eShaderStage stage)
	{
		UINT slot = (UINT)mType;
		switch (stage)
		{
		case KGraphics::eShaderStage::VS:
			GraphicDevice_DX11::getInstance().GetDeviceContext()->VSSetConstantBuffers(slot, 1, buffer.GetAddressOf());
			break;
		case KGraphics::eShaderStage::HS:
			GraphicDevice_DX11::getInstance().GetDeviceContext()->HSSetConstantBuffers(slot, 1, buffer.GetAddressOf());
			break;
		case KGraphics::eShaderStage::DS:
			GraphicDevice_DX11::getInstance().GetDeviceContext()->DSSetConstantBuffers(slot, 1, buffer.GetAddressOf());
			break;
		case KGraphics::eShaderStage::GS:
			GraphicDevice_DX11::getInstance().GetDeviceContext()->GSSetConstantBuffers(slot, 1, buffer.GetAddressOf());
			break;
		case KGraphics::eShaderStage::PS:
			GraphicDevice_DX11::getInstance().GetDeviceContext()->PSSetConstantBuffers(slot, 1, buffer.GetAddressOf());
			break;
		case KGraphics::eShaderStage::CS:
			GraphicDevice_DX11::getInstance().GetDeviceContext()->CSSetConstantBuffers(slot, 1, buffer.GetAddressOf());
			break;
		case KGraphics::eShaderStage::All:
			GraphicDevice_DX11::getInstance().GetDeviceContext()->VSSetConstantBuffers(slot, 1, buffer.GetAddressOf());
			GraphicDevice_DX11::getInstance().GetDeviceContext()->HSSetConstantBuffers(slot, 1, buffer.GetAddressOf());
			GraphicDevice_DX11::getInstance().GetDeviceContext()->DSSetConstantBuffers(slot, 1, buffer.GetAddressOf());
			GraphicDevice_DX11::getInstance().GetDeviceContext()->GSSetConstantBuffers(slot, 1, buffer.GetAddressOf());
			GraphicDevice_DX11::getInstance().GetDeviceContext()->PSSetConstantBuffers(slot, 1, buffer.GetAddressOf());
			GraphicDevice_DX11::getInstance().GetDeviceContext()->CSSetConstantBuffers(slot, 1, buffer.GetAddressOf());
			break;
		default:
			break;
		}
	}
}
