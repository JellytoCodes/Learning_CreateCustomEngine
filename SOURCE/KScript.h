#pragma once
#include "KComponent.h"

namespace KEngine
{
	class Collider;

	class Script : public Component
	{
		using Super = Component;

	public :
		Script();
		~Script();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;
		void Release() override;

		virtual void OnCollisionEnter(Collider* other);
		virtual void OnCollisionStay(Collider* other);
		virtual void OnCollisionExit(Collider* other);
	private :

	};
}

