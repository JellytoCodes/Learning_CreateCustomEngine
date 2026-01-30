#pragma once

#include "../SOURCE/KResources.h"
#include "../SOURCE/KTexture.h"


namespace KEngine
{
	void LoadResources()
	{
		Resources::Load<KEngine::Texture>(L"Map", L"..\\Resources\\Map.png");
		Resources::Load<KEngine::Texture>(L"Ori", L"..\\Resources\\Ori.png");
		Resources::Load<KEngine::Texture>(L"Cat", L"..\\Resources\\ChickenAlpha.bmp");
		Resources::Load<KEngine::Texture>(L"Bubble", L"..\\Resources\\Bubble.png");
		Resources::Load<KEngine::Texture>(L"Effect", L"..\\Resources\\effect.png");
	}
}