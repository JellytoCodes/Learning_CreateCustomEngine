#include "KAudioListener.h"

#include "GameObject.h"
#include "KTransform.h"
#include "KFmod.h"

namespace KEngine
{
	AudioListener::AudioListener()
		: Super(eComponentType::AudioListener)
	{
	}

	AudioListener::~AudioListener()
	{
	}

	void AudioListener::Initialize()
	{
		
	}

	void AudioListener::Update()
	{
		
	}

	void AudioListener::LateUpdate()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();

		//Fmod::Set3DListenerAttributes(pos);
	}

	void AudioListener::Render()
	{
		
	}

	void AudioListener::Release()
	{
		
	}
}
