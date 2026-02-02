#pragma once

#include "../SOURCE/KResources.h"
#include "../SOURCE/KTexture.h"

namespace KEngine
{
	void LoadResources()
	{
		Resources::Load<Texture>(L"Cat", L"..\\Resources\\ChickenAlpha.bmp");
		Resources::Load<Texture>(L"Player", L"..\\Resources\\Player.bmp");
		Resources::Load<Texture>(L"SpringFloor", L"..\\Resources\\SpringFloor.bmp");
	}
}