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

		COLORREF			GetPixel(int x, int y);
		void				Release() override;

		UINT				GetWidth()							{ return mWidth; }
		void				SetWidth(UINT width)				{ mWidth = width; }

		UINT				GetHeight()							{ return mHeight; }
		void				SetHeight(UINT height)				{ mHeight = height; }

		HDC					GetHdc()							{ return mHdc; }
		eTextureType		GetTextureType()					{ return mTextureType; }
		Gdiplus::Image*		GetImage()							{ return mImage.get(); }

		bool				IsAlpha()							{ return mbAlpha; }

	private :
		eTextureType						mTextureType;
		std::unique_ptr<Gdiplus::Image>		mImage;
		HBITMAP								mBitmap;
		HDC									mHdc;

		bool								mbAlpha;
		UINT								mWidth;
		UINT								mHeight;
	};	
}


