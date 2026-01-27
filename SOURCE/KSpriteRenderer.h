#pragma once
#include "KComponent.h"

namespace KEngine
{
	class SpriteRenderer : public Component
	{
	public:
		SpriteRenderer();
		virtual ~SpriteRenderer();

		void Initialize() override;
		void Update()  override;
		void LateUpdate()  override;
		void Render(HDC hdc)  override;
		void Release() override;

		void LoadImage(const std::wstring& path);
	private:
		std::shared_ptr<Gdiplus::Image> mImage;
		UINT mWidth;
		UINT mHeight;
	};
}

