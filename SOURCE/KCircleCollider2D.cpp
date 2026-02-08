#include "KCircleCollider2D.h"
#include "GameObject.h"
#include "KTransform.h"

namespace KEngine
{
	CircleCollider2D::CircleCollider2D()
		: Collider(eColliderType::Circle2D),
		mRadius(0)
	{

	}

	CircleCollider2D::~CircleCollider2D()
	{
	}

	void CircleCollider2D::Initialize()
	{
		
	}

	void CircleCollider2D::Update()
	{
		
	}

	void CircleCollider2D::LateUpdate()
	{
		
	}

	void CircleCollider2D::Render()
	{
		if (GameObject* owner = GetOwner())
		{
			Transform* transform = owner->GetComponent<Transform>();
			KMath::Vector2 pos = transform->GetPosition();
		}
	}

	void CircleCollider2D::Release()
	{
		
	}
}
