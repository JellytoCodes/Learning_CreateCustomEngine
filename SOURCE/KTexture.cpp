#include "KTexture.h"
#include "KApplication.h"

// 해당 전역변수가 존재함을 알리는 키워드
extern KEngine::Application application;

namespace KEngine
{
	Texture::Texture()
		:Super(KEngine::eResourceType::Texture), mImage(nullptr), mWidth(0), mHeight(0)
	{

	}

	Texture::~Texture()
	{
		
	}

	HRESULT Texture::Load(const std::wstring& path)
	{
		std::wstring ext = path.substr(path.find_last_of(L".") + 1);

		if (ext == L"bmp")		// .bmp
		{
			mTextureType = eTextureType::BMP;
			mBitmap = (HBITMAP)LoadImageW(nullptr, path.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

			if (mBitmap == nullptr) return S_FALSE;

			BITMAP info = {};
			GetObject(mBitmap, sizeof(BITMAP), &info);

			mWidth = info.bmWidth;
			mHeight = info.bmHeight;

			HDC mainDC = application.GetHdc();
			mHdc = CreateCompatibleDC(mainDC);

			HBITMAP oldBitmap = (HBITMAP)SelectObject(mHdc, mBitmap);
			DeleteObject(oldBitmap);
		}
		else if (ext == L"png")	// .png
		{
			mTextureType = eTextureType::PNG;
			mImage = std::shared_ptr<Gdiplus::Image>(Gdiplus::Image::FromFile(path.c_str()));
			if (mImage == nullptr) return S_FALSE;

			mWidth = mImage->GetWidth();
			mHeight = mImage->GetHeight();
		}

		return S_OK;
	}

	void Texture::Release()
	{
		mImage = nullptr;
		mBitmap = nullptr;
	}
}
