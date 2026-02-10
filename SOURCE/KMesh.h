#pragma once
#include "KIndexBuffer.h"
#include "KResource.h"
#include "KVertexBuffer.h"

namespace KEngine
{
	class Mesh : public Resource
	{
		using Super = Resource;

	public :
		struct Data
		{
			Data()
				: mTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST),
				vertices{}, indices{}
			{
				
			}
			~Data()
			{
				
			}

			D3D11_PRIMITIVE_TOPOLOGY		mTopology;
			std::vector<KGraphics::Vertex>	vertices;
			std::vector<UINT>				indices;
		};

		Mesh();
		~Mesh();

		HRESULT Save(const std::wstring& path) override;
		HRESULT Load(const std::wstring& path) override;

		void CreateVB(const std::vector<KGraphics::Vertex>& vertices);
		void CreateIB(const std::vector<UINT>& indices);
		void Bind();

		UINT GetIndexCount() const { return mIndexBuffer.GetIndexCount(); }

	private :
		VertexBuffer	mVertexBuffer;
		IndexBuffer		mIndexBuffer;
		Data			mData;
	};
}
