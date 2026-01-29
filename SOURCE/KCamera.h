#pragma once
#include "KComponent.h"

namespace KEngine
{
	class Camera : public Component
	{
		using Super = Component;

	public :
		KMath::Vector2 CalculatePosition(KMath::Vector2 pos) { return pos - mDistance; }

		Camera();
		~Camera();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;
		void Release() override;

	private :
		// std::vector<std::weak_ptr<GameObject>> mGameObjects;

		KMath::Vector2 mDistance;
		KMath::Vector2 mResolution;
		KMath::Vector2 mLookPosition;
		std::weak_ptr<GameObject> mTarget;
	};	
}


