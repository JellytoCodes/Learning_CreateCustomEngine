#include "KCollisionManager.h"
#include "KScene.h"
#include "KSceneManager.h"
#include "GameObject.h"
#include "KCollider.h"
#include "KTransform.h"

namespace KEngine
{
	std::bitset<(UINT)eLayerType::Max> CollisionManager::mCollisionLayerMatrix[(UINT)eLayerType::Max] = {};
	std::unordered_map<UINT64, bool> CollisionManager::mCollisionMap = {};
	void CollisionManager::Initialize()
	{
		
	}

	void CollisionManager::Update()
	{
		auto scene = SceneManager::GetActiveScene();

		for (UINT row = 0 ; row < (UINT)eLayerType::Max ; row++)
		{
			for (UINT col = 0 ; col < (UINT)eLayerType::Max ; col++)
			{
				if (mCollisionLayerMatrix[row][col] == true)
				{
					LayerCollision(scene, (eLayerType)row, (eLayerType)col);
				}
			}
		}
	}

	void CollisionManager::LateUpdate()
	{
		
	}

	void CollisionManager::Render(HDC hdc)
	{
		
	}

	void CollisionManager::Clear()
	{
		mCollisionMap.clear();
		mCollisionLayerMatrix->reset();
	}

	void CollisionManager::CollisionLayerCheck(eLayerType left, eLayerType right, bool enable)
	{
		int row = 0;
		int col = 0;

		if (left <= right)
		{
			row = (UINT)left;
			col = (UINT)right;
		}
		else
		{
			row = (UINT)right;
			col = (UINT)left;
		}

		mCollisionLayerMatrix[row][col] = enable;
	}

	void CollisionManager::LayerCollision(Scene* scene, eLayerType left, eLayerType right)
	{
		std::vector<GameObject*> lefts = SceneManager::GetGameObjects(left);
		std::vector<GameObject*> rights = SceneManager::GetGameObjects(right);

		for (auto& leftObject : lefts)
		{
			if (leftObject->IsActive() == false) continue;

			Collider* leftCollider = leftObject->GetComponent<Collider>();
			if (leftCollider == nullptr) continue;

			for (auto& rightObject : rights)
			{
				if (rightObject->IsActive() == false) continue;

				Collider* rightCollider = rightObject->GetComponent<Collider>();
				if (rightCollider == nullptr) continue;
				if (leftObject == rightObject) continue;

				ColliderCollision(leftCollider, rightCollider);
			}
		}
	}

	void CollisionManager::ColliderCollision(Collider* left, Collider* right)
	{
		// 두 충돌체 번호를 가져온 ID를 확인해서 CollisionID값을 세팅
		CollisionID id = {};
		id.left = left->GetID();
		id.right = right->GetID();

		// 해당ID로 충돌체 정보를 검색
		// 만약 충돌체 정보가 없다면 충돌체 정보를 준다.
		auto iter = mCollisionMap.find(id.id);
		if (iter == mCollisionMap.end())
		{
			mCollisionMap.insert(std::make_pair(id.id, false));
			iter = mCollisionMap.find(id.id);
		}

		// 충돌 체크
		if (Intersect(left, right))
		{
			// 최초 충돌
			if (iter->second == false)
			{
				left->OnCollisionEnter(right);
				right->OnCollisionEnter(left);
				iter->second = true;
			}

			// 충돌 중
			else
			{
				left->OnCollisionStay(right);
				right->OnCollisionStay(left);
			}
		}
		else
		{
			// 충돌 중 충돌 영역을 벗어났을 때
			if (iter->second == true)
			{
				left->OnCollisionExit(right);
				right->OnCollisionExit(left);
			}
		}
	}

	bool CollisionManager::Intersect(Collider* left, Collider* right)
	{
		Transform* leftTransform = left->GetOwner()->GetComponent<Transform>();
		Transform* rightTransform = right->GetOwner()->GetComponent<Transform>();

		KMath::Vector2 leftPos = leftTransform->GetPosition() + left->GetOffset();
		KMath::Vector2 rightPos = rightTransform->GetPosition() + right->GetOffset();

		// size 1, 1 기본 크기가 100픽셀
		KMath::Vector2 leftSize = left->GetSize() * 100.f;
		KMath::Vector2 rightSize = right->GetSize() * 100.f;

		// AABB 충돌

		// Rect - Rect
		if (left->GetColliderType() == eColliderType::Rect2D && right->GetColliderType() == eColliderType::Rect2D)
		{
			return
			fabs(leftPos.x - rightPos.x) < fabs((leftSize.x / 2.f) + (rightSize.x / 2.f)) &&
			fabs(leftPos.y - rightPos.y) < fabs((leftSize.y / 2.f) + (rightSize.y / 2.f));
		}

		// Circle - Circle
		if (left->GetColliderType() == eColliderType::Circle2D && right->GetColliderType() == eColliderType::Circle2D)
		{
			KMath::Vector2 leftCirclePos = leftPos + (leftSize / 2.0f);
			KMath::Vector2 rightCirclePos = rightPos + (rightSize / 2.0f);
			float distance = (leftCirclePos - rightCirclePos).Length();

			return distance <= (leftSize.x / 2.0f + rightSize.x / 2.0f);
		}

		// Circle - Rect
		if ((left->GetColliderType() == eColliderType::Circle2D && right->GetColliderType() == eColliderType::Rect2D)
		||(left->GetColliderType() == eColliderType::Rect2D && right->GetColliderType() == eColliderType::Circle2D))
		{
		    Collider* circle = (left->GetColliderType() == eColliderType::Circle2D) ? left : right;
		    Collider* rect = (circle == left) ? right : left;

			KMath::Vector2 cPos = circle->GetOwner()->GetComponent<Transform>()->GetPosition() + circle->GetOffset();
			KMath::Vector2 rPos = rect->GetOwner()->GetComponent<Transform>()->GetPosition() + rect->GetOffset();
			KMath::Vector2 rSize = rect->GetSize() * 100.f;
		    float radius = (circle->GetSize().x * 100.f) / 2.0f;

		    float closestX = max(rPos.x - rSize.x / 2.0f, min(cPos.x, rPos.x + rSize.x / 2.0f));
		    float closestY = max(rPos.y - rSize.y / 2.0f, min(cPos.y, rPos.y + rSize.y / 2.0f));

		    float distSq = (cPos.x - closestX) * (cPos.x - closestX) + (cPos.y - closestY) * (cPos.y - closestY);

		    return distSq <= (radius * radius);
		}

		return false;
	}
}
