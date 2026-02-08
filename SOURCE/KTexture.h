#pragma once
#include "KResource.h"

namespace KEngine
{
	class Texture : public KEngine::Resource
	{
		using Super = Resource;

	public :
		enum class eTextureType
		{
			BMP,
			PNG,
			None,
		};

		static Texture*		Create(const std::wstring& name, UINT width, UINT height);
		

		Texture();
		virtual ~Texture();

		HRESULT				Load(const std::wstring& path) override;

		void				Release() override;

		UINT				GetWidth() const					{ return mWidth; }
		void				SetWidth(UINT width)				{ mWidth = width; }

		UINT				GetHeight() const					{ return mHeight; }
		void				SetHeight(UINT height)				{ mHeight = height; }

	private :
		eTextureType						mTextureType;

		bool								mbAlpha;
		UINT								mWidth;
		UINT								mHeight;
	};	
}


