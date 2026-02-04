#include "KUIHUD.h"

#include "KResources.h"

namespace KEngine
{
	UIHUD::UIHUD()
		: Super(eUIType::HpBar), mTexture(nullptr)
	{

	}

	UIHUD::~UIHUD()
	{

	}

	void UIHUD::OnInit()
	{
		mTexture = Resources::Find<Texture>(L"HPBAR");
	}

	void UIHUD::OnActive()
	{
		
	}

	void UIHUD::OnInActive()
	{
		
	}

	void UIHUD::OnUpdate()
	{
		
	}

	void UIHUD::OnLateUpdate()
	{
		
	}

	void UIHUD::OnRender(HDC hdc)
	{

		TransparentBlt(hdc
			, 0, 0
			, mTexture->GetWidth()
			, mTexture->GetHeight()
			, mTexture->GetHdc()
			, 0, 0
			, mTexture->GetWidth() / 2.0f
			, mTexture->GetHeight()
			, RGB(255, 0, 255));	
	}

	void UIHUD::OnClear()
	{
		
	}
}
