#pragma once
#include "KUIBase.h"
#include "KTexture.h"

namespace KEngine
{
	class UIHUD : public UIBase
	{
		using Super = UIBase;
	public:
		UIHUD();
		~UIHUD();

		virtual void OnInit() override;
		virtual void OnActive() override;
		virtual void OnInActive() override;
		virtual void OnUpdate() override;
		virtual void OnLateUpdate() override;
		virtual void OnRender() override;
		virtual void OnClear() override;

	private:
		Texture* mTexture;
	};
}