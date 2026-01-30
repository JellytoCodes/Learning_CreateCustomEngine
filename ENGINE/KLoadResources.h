#pragma once

#include "../SOURCE/KResources.h"
#include "../SOURCE/KTexture.h"


namespace KEngine
{
	void LoadResources()
	{
		Resources::Load<KEngine::Texture>(L"Map", L"D:\\Dev\\Programming_Study\\Learning_CreateCustomEngine\\Resources\\Map.png");
		Resources::Load<KEngine::Texture>(L"Ori", L"D:\\Dev\\Programming_Study\\Learning_CreateCustomEngine\\Resources\\Ori.png");
		Resources::Load<KEngine::Texture>(L"Cat", L"D:\\Dev\\Programming_Study\\Learning_CreateCustomEngine\\Resources\\ChickenAlpha.bmp");
	}
}
