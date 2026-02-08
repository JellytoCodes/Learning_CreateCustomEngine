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

		Texture* rawTexture = image.get();

		Resources::Insert(name, std::move(image));

		return rawTexture;
	}

	Texture::Texture()
    : Super(KEngine::eResourceType::Texture),
    mTextureType(eTextureType::None), mbAlpha(false), mWidth(0), mHeight(0)
	{

	}

	Texture::~Texture()
	{

	}

	HRESULT Texture::Load(const std::wstring& path)
	{
		std::wstring ext = path.substr(path.find_last_of(L".") + 1);

		return S_OK;
	}

	void Texture::Release()
	{

	}
}
