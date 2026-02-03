#include "KFloorScript.h"

#include "KTransform.h"
#include "KRigidBody.h"
#include "GameObject.h"
#include "KCollider.h"

namespace KEngine
{
	FloorScript::FloorScript()
	{
	}

	FloorScript::~FloorScript()
	{
	}

	void FloorScript::Initialize()
	{
		
	}

	void FloorScript::Update()
	{
		
	}

	void FloorScript::LateUpdate()
	{
		
	}

	void FloorScript::Render(HDC hdc)
	{
		
	}

	void FloorScript::Release()
	{
		
	}

	void FloorScript::OnCollisionEnter(Collider* other)
	{
		RigidBody* playerRb = other->GetOwner()->GetComponent<RigidBody>();
		Transform* playerTr = other->GetOwner()->GetComponent<Transform>();
		Collider* playerCol = other;

		RigidBody* floorRb = this->GetOwner()->GetComponent<RigidBody>();
		Transform* floorTr = this->GetOwner()->GetComponent<Transform>();
		Collider* floorCol = this->GetOwner()->GetComponent<Collider>();

		float len = fabs(playerTr->GetPosition().y - floorTr->GetPosition().y);
		float scale = fabs(playerCol->GetSize().y * 100 / 2.0f - floorCol->GetSize().y * 100 / 2.0f);

		if (len < scale)
		{
			KMath::Vector2 playerPos = playerTr->GetPosition();
			playerPos.y -= (scale - len) - 1.0f;

			playerTr->SetPosition(playerPos);
		}
		
		playerRb->SetGround(true);
	}

	void FloorScript::OnCollisionStay(Collider* other)
	{
		
	}

	void FloorScript::OnCollisionExit(Collider* other)
	{
		
	}
}
