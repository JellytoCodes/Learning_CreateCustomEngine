#include "KAudioSource.h"

#include "GameObject.h"
#include "KTransform.h"
#include "KFmod.h"

namespace KEngine
{
	AudioSource::AudioSource()
		: Super(eComponentType::AudioSource)
	{
	}

	AudioSource::~AudioSource()
	{
	}

	void AudioSource::Initialize()
	{
		
	}

	void AudioSource::Update()
	{
		
	}

	void AudioSource::LateUpdate()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		KMath::Vector2 pos = tr->GetPosition();

		mAudioClip->Set3DAttributes(pos);
	}

	void AudioSource::Render(HDC hdc)
	{
		
	}

	void AudioSource::Release()
	{
		
	}

	void AudioSource::Play()
	{
		mAudioClip->Play();
	}

	void AudioSource::Stop()
	{
		mAudioClip->Stop();
	}

	void AudioSource::SetLoop(bool loop)
	{
		mAudioClip->SetLoop(loop);
	}
}
