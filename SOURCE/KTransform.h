#pragma once
#include "KComponent.h"

namespace KEngine
{
	class Transform : public Component
	{
		using Super = Component;

	public:
		Transform();
		virtual ~Transform();

		void Initialize() override;
		void Update()  override;
		void LateUpdate()  override;
		void Render(HDC hdc)  override;

		void SetPosition(KMath::Vector2 pos) { mPos.x = pos.x; mPos.y = pos.y; }
		KMath::Vector2 GetPosition() { return mPos; }

	private:
		KMath::Vector2 mPos;
	};
}
