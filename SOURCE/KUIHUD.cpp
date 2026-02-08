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

	void UIHUD::OnRender()
	{

	}

	void UIHUD::OnClear()
	{
		
	}
}
