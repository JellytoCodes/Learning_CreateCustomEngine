#pragma once

#include "../SOURCE/KResources.h"
#include "../SOURCE/KTexture.h"
//#include "../SOURCE/KAudioClip.h"

namespace KEngine
{
	void LoadResources()
	{
		Resources::Load<Texture>(L"Cat", L"..\\Resources\\ChickenAlpha.bmp");
		Resources::Load<Texture>(L"Player", L"..\\Resources\\Player.bmp");
		Resources::Load<Texture>(L"SpringFloor", L"..\\Resources\\SpringFloor.bmp");
		Resources::Load<Texture>(L"HPBAR", L"..\\Resources\\HPBAR.bmp");
		Resources::Load<Texture>(L"PixelMap", L"..\\Resources\\pixelMap.bmp");

		//Resources::Load<AudioClip>(L"BGSound", L"..\\Resources\\Sound\\smw_bonus_game_end.wav")
	}
}