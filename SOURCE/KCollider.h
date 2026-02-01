#pragma once
#include "KComponent.h"
namespace KEngine
{
	class Collider : public Component
	{
		using Super = Component;
	public :
		Collider(eColliderType colliderType);
		~Collider();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;
		void Release() override;

		virtual void OnCollisionEnter(Collider* other);
		virtual void OnCollisionStay(Collider* other);
		virtual void OnCollisionExit(Collider* other);

		KMath::Vector2 GetOffset() const { return mOffset; }
		void SetOffset(const KMath::Vector2 offset) { mOffset = offset; }

		KMath::Vector2 GetSize() { return mSize; }
		void SetSize(KMath::Vector2 size) { mSize = size; }

		eColliderType GetColliderType() { return mColliderType; }

		UINT32 GetID() { return mID; }

	protected :
		eColliderType mColliderType;

		static UINT32 mCollisionID;
		UINT32 mID;
		KMath::Vector2 mOffset;
		KMath::Vector2 mSize;
	};
}
