#include "KBoxCollider2D.h"

#include "GameObject.h"
#include "KRenderer.h"
#include "KTransform.h"
#include "KCamera.h"

namespace KEngine
{
	BoxCollider2D::BoxCollider2D()
		: Collider(eColliderType::Rect2D)
	{

	}

	BoxCollider2D::~BoxCollider2D()
	{

	}

	void BoxCollider2D::Initialize()
	{
		
	}

	void BoxCollider2D::Update()
	{
		
	}

	void BoxCollider2D::LateUpdate()
	{
		
	}

	void BoxCollider2D::Render()
	{
		if (GameObject* owner = GetOwner())
		{
			Transform* transform = owner->GetComponent<Transform>();
			KMath::Vector2 pos = transform->GetPosition();
		}
	}

	void BoxCollider2D::Release()
	{
		
	}
}
