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

		static std::shared_ptr<Texture> Create(const std::wstring& name, UINT width, UINT height);

		Texture();
		virtual ~Texture();

		HRESULT Load(const std::wstring& path) override;

		UINT GetWidth()									{ return mWidth; }
		void SetWidth(UINT width)						{ mWidth = width; }

		UINT GetHeight()								{ return mHeight; }
		void SetHeight(UINT height)						{ mHeight = height; }

		HDC GetHdc()									{ return mHdc; }
		eTextureType GetTextureType()					{ return mTextureType; }
		std::shared_ptr<Gdiplus::Image> GetImage()		{ return mImage; }

		bool IsAlpha() { return mbAlpha; }

		void Release() override;

	private :
		eTextureType mTextureType;
		std::shared_ptr<Gdiplus::Image> mImage;
		HBITMAP mBitmap;
		HDC mHdc;

		bool mbAlpha;
		UINT mWidth;
		UINT mHeight;
	};	
}


