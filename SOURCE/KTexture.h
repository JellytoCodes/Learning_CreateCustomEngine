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

		Texture();
		virtual ~Texture();

		HRESULT Load(const std::wstring& path) override;

		UINT GetWidth()									{ return mWidth; }
		UINT GetHeight()								{ return mHeight; }
		HDC GetHdc()									{ return mHdc; }
		eTextureType GetTextureType()					{ return mTextureType; }
		std::shared_ptr<Gdiplus::Image> GetImage()		{ return mImage; }

		void Release() override;

	private :
		eTextureType mTextureType;
		std::shared_ptr<Gdiplus::Image> mImage;
		HBITMAP mBitmap;
		HDC mHdc;

		UINT mWidth;
		UINT mHeight;
	};	
}


