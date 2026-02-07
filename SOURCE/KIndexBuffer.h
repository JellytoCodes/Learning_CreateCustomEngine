#pragma once
#include "KGraphicDevice_DX11.h"

namespace KEngine
{
	class IndexBuffer : public KGraphics::GPUBuffer
	{
	public :
		IndexBuffer();
		~IndexBuffer();

		/*
		[Init: Index Buffer 생성]
		목적:
		- 인덱스 데이터를 GPU 리소스로 생성하여 DrawIndexed에서 사용할 준비를 한다.

		설정 의미:
		- BindFlags=INDEX_BUFFER: IA가 인덱스 스트림으로 읽는다.
		- Usage=DEFAULT: 보통 한 번 업로드 후 잘 안 바꾸는 정적 데이터에 적합.

		파이프라인 소비:
		- IASetIndexBuffer로 바인딩
		- DrawIndexed의 indexCount만큼 이 버퍼를 읽어 정점 조립을 수행
		*/
		void Create(const std::vector<UINT>& indices);

		void Bind();
	private :
	};
}
