#include "KTexture.h"

#include <memory>

#include "KApplication.h"
#include "KResources.h"

// 해당 전역변수가 존재함을 알리는 키워드
extern KEngine::Application application;

namespace KEngine
{
	Texture* Texture::Create(const std::wstring& name, UINT width, UINT height)
	{
		if (Texture* findTexture = Resources::Find<Texture>(name))	return findTexture;

		auto image = std::make_unique<Texture>();

		// 가비지 쓰레기 값 때문에 명시적으로 BMP 사용 표기
		image->mTextureType = eTextureType::BMP;

		image->SetName(name);
		image->SetWidth(width);
		image->SetHeight(height);

		HDC hdc = application.GetHdc();
		HWND hwnd = application.GetHwnd();

		image->mBitmap = CreateCompatibleBitmap(hdc, width, height);
		image->mHdc = CreateCompatibleDC(hdc);

		{
			HBRUSH transparentBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
			HBRUSH oldBrush = (HBRUSH)SelectObject(image->mHdc, transparentBrush);

			Rectangle(image->mHdc, -1, -1, image->GetWidth() + 1, image->GetHeight() + 1);

			SelectObject(image->mHdc, oldBrush);
		}

		SelectObject(image->mHdc, image->mBitmap);

		Texture* rawTexture = image.get();

		Resources::Insert(name, std::move(image));

		return rawTexture;
	}

	Texture::Texture()
    : Super(KEngine::eResourceType::Texture),
    mTextureType(eTextureType::None),
    mImage(nullptr), mBitmap(nullptr), mHdc(nullptr),                   
    mbAlpha(false), mWidth(0), mHeight(0)
	{

	}

	Texture::~Texture()
	{
		if (mHdc)		DeleteDC(mHdc);
		if (mBitmap)	DeleteObject(mBitmap);
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

			if (info.bmBitsPixel == 32)			mbAlpha = true;
			else if (info.bmBitsPixel == 24)	mbAlpha = false;

			HDC mainDC = application.GetHdc();
			mHdc = CreateCompatibleDC(mainDC);

			HBITMAP oldBitmap = (HBITMAP)SelectObject(mHdc, mBitmap);
			DeleteObject(oldBitmap);
		}
		else if (ext == L"png")	// .png
		{
			mTextureType = eTextureType::PNG;
			mImage = std::unique_ptr<Gdiplus::Image>(Gdiplus::Image::FromFile(path.c_str()));
			if (mImage == nullptr) return S_FALSE;

			mWidth = mImage->GetWidth();
			mHeight = mImage->GetHeight();
		}

		return S_OK;
	}

	void Texture::Release()
	{
		mImage.reset();
		mBitmap = nullptr;
	}
}
