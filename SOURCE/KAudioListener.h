#pragma once
#include "KFmod.h"
#include "KComponent.h"

namespace KEngine
{
	class AudioListener : public Component
	{
		using Super = Component;

	public :
		AudioListener();
		~AudioListener();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;
		void Release() override;

	private :
	};	
}


