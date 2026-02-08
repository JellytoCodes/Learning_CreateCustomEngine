#pragma once
#include "KComponent.h"
#include "KAudioClip.h"

namespace KEngine
{
	class AudioSource : public Component
	{
		using Super = Component;

	public :
		AudioSource();
		~AudioSource();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;
		void Release() override;

		void Play();
		void Stop();
		void SetLoop(bool loop);

		void SetClip(AudioClip* clip) { mAudioClip = clip; }
		AudioClip* GetAudioClip() { return mAudioClip; }

	private :
		AudioClip* mAudioClip;
	};	
}
