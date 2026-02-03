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

	void BoxCollider2D::Render(HDC hdc)
	{
		if (GameObject* owner = GetOwner())
		{
			Transform* transform = owner->GetComponent<Transform>();
			KMath::Vector2 pos = transform->GetPosition();

			if (KRenderer::mainCamera) pos = KRenderer::mainCamera->CalculatePosition(pos);

			HBRUSH transparentBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
			HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, transparentBrush);

			HPEN greenPen = CreatePen(PS_SOLID, 2, RGB(0, 255, 0));
			HPEN oldPen = (HPEN)SelectObject(hdc, greenPen);

			
			KMath::Vector2 size = GetSize() * 100.f; // 충돌 로직과 동일한 크기 사용
			KMath::Vector2 finalPos = pos + mOffset;

			
			Rectangle(hdc, (int)finalPos.x, (int)finalPos.y, (int)(finalPos.x + size.x), (int)(finalPos.y + size.y));

			SelectObject(hdc, oldBrush);
			SelectObject(hdc, oldPen);

			DeleteObject(greenPen);
		}
	}

	void BoxCollider2D::Release()
	{
		
	}
}
