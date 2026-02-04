#include "KAudioClip.h"

namespace KEngine
{
	AudioClip::AudioClip()
		: Super(eResourceType::AudioClip),
		mSound(nullptr), mChannel(nullptr), mMinDistance(1.f), mMaxDistance(1000.f), mbLoop(false)
	{

	}

	AudioClip::~AudioClip()
	{
		mSound->release();
		mSound = nullptr;
	}

	HRESULT AudioClip::Load(const std::wstring& path)
	{
		std::string cPath(path.begin(), path.end());
		if (!Fmod::CreateSound(cPath, &mSound))	return S_FALSE;

		mSound->set3DMinMaxDistance(mMinDistance, mMaxDistance);

		return S_OK;

	}

	void AudioClip::Play()
	{
		if (mbLoop) mSound->setMode(FMOD_LOOP_NORMAL);
		else		mSound->setMode(FMOD_LOOP_OFF);

		Fmod::SoundPlay(mSound, &mChannel);
	}

	void AudioClip::Stop()
	{
		mChannel->stop();
	}

	void AudioClip::Set3DAttributes(const KMath::Vector2 pos)
	{
		FMOD_VECTOR fmodPos(0.f, 0.f, 0.f);
		FMOD_VECTOR fmodVel(0.f, 0.f, 0.f);

		mChannel->set3DAttributes(&fmodPos, &fmodVel);
	}
}
