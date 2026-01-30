#pragma once

#include "../SOURCE/KResources.h"
#include "../SOURCE/KTexture.h"


namespace KEngine
{
	void LoadResources()
	{
		Resources::Load<KEngine::Texture>(L"Cat", L"..\\Resources\\ChickenAlpha.bmp");
		Resources::Load<KEngine::Texture>(L"Player", L"..\\Resources\\Player.bmp");
	}
}