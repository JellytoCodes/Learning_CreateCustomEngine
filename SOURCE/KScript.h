#pragma once
#include "KComponent.h"

namespace KEngine
{
	class Script : public Component
	{
		using Super = Component;

	public :
		Script();
		~Script();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;
		void Release() override;

	private :

	};
}

