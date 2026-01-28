#pragma once
#include "KEntity.h"

namespace KEngine
{
	// 게임에서 사용되는 데이터들의 종류
	class Resource : public Entity
	{
	public :
		Resource(KEngine::eResourceType type);
		virtual ~Resource();

		virtual HRESULT Load(const std::wstring& path) = 0;

		const std::wstring& GetPath() { return mPath; }
		void SetPath(const std::wstring& path) { mPath = path; }
	private :
		KEngine::eResourceType mType;
		std::wstring mPath;

	};
}


