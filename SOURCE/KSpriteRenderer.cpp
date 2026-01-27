#include "KSpriteRenderer.h"

#include "GameObject.h"
#include "KTransform.h"

namespace KEngine
{
	SpriteRenderer::SpriteRenderer()
		: mImage(nullptr), mWidth(0), mHeight(0)
	{

	}

	SpriteRenderer::~SpriteRenderer()
	{
		
	}

	void SpriteRenderer::Initialize()
	{

	}

	void SpriteRenderer::Update()
	{

	}

	void SpriteRenderer::LateUpdate()
	{

	}

	void SpriteRenderer::Render(HDC hdc)
	{
		// DC(Device Context)란 화면에 출력에 필요한 모든 정보(폰트, 선의 굵기, 색상 등을 어떻게 그려줄 것인지)를 
        // 가지는 데이터 구조체이며 GDI모듈에 의해 관리된다.
        // 화면 출력에 필요한 모든 경우는 WINAPI에서는 DC를 통해서 작업을 진행할 수 있다.

		std::shared_ptr<Transform> tr = GetOwner().lock()->GetComponent<Transform>();

		KMath::Vector2 pos = tr->GetPosition();

		Gdiplus::Graphics graphics(hdc);
		graphics.DrawImage(mImage.get(), Gdiplus::Rect(pos.x, pos.y, mWidth, mHeight));
	}

	void SpriteRenderer::Release()
	{
		mImage = nullptr;
	}

	void SpriteRenderer::LoadImage(const std::wstring& path)
	{
		mImage = std::shared_ptr<Gdiplus::Image>(Gdiplus::Image::FromFile(path.c_str()));
		mWidth = mImage->GetWidth();
		mHeight = mImage->GetHeight();
	}
}
