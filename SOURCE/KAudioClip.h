#pragma once
#include "KFmod.h"
#include "KResource.h"

namespace KEngine
{
	class AudioClip : public Resource
	{
		using Super = Resource;

	public :
		AudioClip();
		virtual ~AudioClip();

		HRESULT Load(const std::wstring& path) override;

		void Play();
		void Stop();
		void Set3DAttributes(const KMath::Vector3 pos);
		void SetLoop(bool loop) {mbLoop = loop; }

	private:
		FMOD::Sound* mSound;
		FMOD::Channel* mChannel;

		float mMinDistance;
		float mMaxDistance;
		bool mbLoop;
	};	
}



