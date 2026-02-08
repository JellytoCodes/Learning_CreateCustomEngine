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

		void				Initialize() override;
		void				Update()  override;
		void				LateUpdate()  override;
		void				Render()  override;

		void				SetPosition(KMath::Vector2 pos)		{ mPos.x = pos.x; mPos.y = pos.y; }
		KMath::Vector2		GetPosition() const					{ return mPos; }

		void				SetScale(KMath::Vector2 scale)		{ mScale.x = scale.x; mScale.y = scale.y; }
		KMath::Vector2		GetScale() const					{ return mScale; }

		void				SetRotation(float rotation)			{ mRotation = rotation; }
		float				GetRotation() const					{ return mRotation; }

	private:
		KMath::Vector2	mPos;
		KMath::Vector2	mScale;
		float			mRotation;
	};
}
