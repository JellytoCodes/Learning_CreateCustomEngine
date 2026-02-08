#include "KCollider.h"
#include "KScript.h"
#include "GameObject.h"

namespace KEngine
{
	UINT32 Collider::mCollisionID = 1;
	Collider::Collider(eColliderType colliderType)
		: Super(eComponentType::Collider),
		mColliderType(colliderType), mID(mCollisionID++), mSize(KMath::Vector2::One)
	{

	}

	Collider::~Collider()
	{

	}

	void Collider::Initialize()
	{
		Component::Initialize();
	}

	void Collider::Update()
	{
		Component::Update();
	}

	void Collider::LateUpdate()
	{
		Component::LateUpdate();
	}

	void Collider::Render()
	{
		Component::Render();
	}

	void Collider::Release()
	{
		Component::Release();
	}

	void Collider::OnCollisionEnter(Collider* other)
	{
		Script* script = GetOwner()->GetComponent<Script>();
		script->OnCollisionEnter(other);
	}

	void Collider::OnCollisionStay(Collider* other)
	{
		Script* script = GetOwner()->GetComponent<Script>();
		script->OnCollisionStay(other);
	}

	void Collider::OnCollisionExit(Collider* other)
	{
		Script* script = GetOwner()->GetComponent<Script>();
		script->OnCollisionExit(other);
	}
}
