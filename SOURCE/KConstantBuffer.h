#pragma once
#include "KGraphicDevice_DX11.h"

namespace KEngine
{
	class ConstantBuffer : public KGraphics::GPUBuffer
	{
	public :
		ConstantBuffer();
		~ConstantBuffer();

		/*
		[Init: Constant Buffer 생성]
		목적:
		- 셰이더에서 참조하는 작은 상수 데이터 묶음을 담는 버퍼 생성.
		- 일반적으로 Transform(행렬), 오브젝트/카메라 파라미터, 시간값 등을 넣는다.

		설정 의미:
		- BindFlags=CONSTANT_BUFFER: b# 슬롯에 바인딩 가능
		- Usage=DYNAMIC + CPUAccess=WRITE: CPU가 Map으로 값 갱신 가능
		- ByteWidth: 16바이트 배수 권장(정렬 규칙). Vector4는 16B.
		*/
		void Create(KGraphics::eCBType type, UINT size, void* data = NULL);

		void SetData(void* data);
		void BindConstantBuffer(KGraphics::eShaderStage stage);

	private :
		UINT				mSize;
		KGraphics::eCBType	mType;
	};
}
