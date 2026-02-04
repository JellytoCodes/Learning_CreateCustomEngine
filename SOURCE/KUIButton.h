#pragma once
#include "KUIBase.h"
#include "KTexture.h"

namespace KEngine
{
	class UIButton : public UIBase
	{
		using Super = UIBase;
	public:
		UIButton();
		~UIButton();

		virtual void OnInit() override;
		virtual void OnActive() override;
		virtual void OnInActive() override;
		virtual void OnUpdate() override;
		virtual void OnLateUpdate() override;
		virtual void OnRender(HDC hdc) override;
		virtual void OnClear() override;

		void ButtonClick();

	private:
		Texture* mTexture;
		Event mOnClick;
	};
}