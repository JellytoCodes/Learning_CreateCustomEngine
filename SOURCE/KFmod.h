#pragma once

#include "CommonInclude.h"
#include "Fmod/fmod_studio.hpp"
#include "Fmod/fmod.hpp"
#include "Fmod/fmod_common.h"
#include "Fmod/fmod_codec.h"

#ifdef _DEBUG
#pragma  comment(lib, "..\\External\\Library\\Fmod\\Debug\\fmodL_vc.lib")
#pragma  comment(lib, "..\\External\\Library\\Fmod\\Debug\\fmodstudioL_vc.lib")
#else
#pragma  comment(lib, "..\\External\\Library\\Fmod\\Release\\fmod_vc.lib")
#pragma  comment(lib, "..\\External\\Library\\Fmod\\Release\\fmodstudioL_vc.lib")
#endif

namespace KEngine
{
	class Fmod
	{
	public :
		static void Initialize();
		static bool CreateSound(const std::string& path, FMOD::Sound** sound);
		static void SoundPlay(FMOD::Sound* sound, FMOD::Channel** channel);
		static void Release();
		static void Set3DListenerAttributes(const KMath::Vector2* pos);
	private :
		static FMOD::Studio::System* mSystem;
		static FMOD::System* mCoreSystem;
	};	
}


