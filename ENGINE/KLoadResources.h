#pragma once

#include "../SOURCE/KResources.h"
#include "../SOURCE/KTexture.h"


namespace KEngine
{
	void LoadResources()
	{
		Resources::Load<KEngine::Texture>(L"BG", L"D:\\Dev\\Programming_Study\\Learning_CreateCustomEngine\\KakaoTalk_20251211_004616658_01.png");
	}
}
