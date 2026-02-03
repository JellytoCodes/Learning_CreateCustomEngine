#pragma once
#include "KCollider.h"

namespace KEngine
{
	class BoxCollider2D : public Collider
	{
	public :
		BoxCollider2D();
		~BoxCollider2D();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;
		void Release() override;

	private :
	};
}