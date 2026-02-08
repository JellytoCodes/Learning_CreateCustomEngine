#pragma once
#include "KCollider.h"

namespace KEngine
{
	class CircleCollider2D : public Collider
	{
	public :
		CircleCollider2D();
		~CircleCollider2D();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;
		void Release() override;

	private :
		float mRadius;
	};
}

