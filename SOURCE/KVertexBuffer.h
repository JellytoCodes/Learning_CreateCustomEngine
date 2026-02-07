#pragma once
#include "KGraphicDevice_DX11.h"

namespace KEngine
{
	class VertexBuffer : public KGraphics::GPUBuffer
	{
	public :
		VertexBuffer();
		~VertexBuffer();

		/*
		[Init: Vertex Buffer 생성]
		목적:
		- 정점 데이터를 GPU 리소스로 생성하여 IA 단계 입력으로 사용할 준비를 한다.

		설정 의미:
		- BindFlags=VERTEX_BUFFER: IA가 정점 스트림으로 읽는다.
		- Usage=DYNAMIC + CPUAccess=WRITE:
		  CPU가 Map/Unmap으로 내용 갱신 가능한 버퍼(수시 업데이트 목적).

		초기 데이터:
		- D3D11_SUBRESOURCE_DATA로 초기 정점 데이터(KRenderer::vertexes) 업로드.
		*/
		void Create(const std::vector<KGraphics::Vertex>& vertexes);

		void Bind();
	private :
	};
}
