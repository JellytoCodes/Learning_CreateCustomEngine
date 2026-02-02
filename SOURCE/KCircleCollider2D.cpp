#include "KCircleCollider2D.h"
#include "GameObject.h"
#include "KTransform.h"

namespace KEngine
{
	CircleCollider2D::CircleCollider2D() : Collider(eColliderType::Circle2D)
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

	void CircleCollider2D::Render(HDC hdc)
	{
		if (GameObject* owner = GetOwner())
		{
			Transform* transform = owner->GetComponent<Transform>();
			KMath::Vector2 pos = transform->GetPosition();

			HBRUSH transparentBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
			HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, transparentBrush);

			HPEN greenPen = CreatePen(PS_SOLID, 2, RGB(0, 255, 0));
			HPEN oldPen = (HPEN)SelectObject(hdc, greenPen);

			KMath::Vector2 rightBottom;
			rightBottom.x = pos.x + mOffset.x + 100 * GetSize().x;
			rightBottom.y = pos.y + mOffset.y + 100 * GetSize().y;

			Ellipse(hdc, pos.x + mOffset.x
			, pos.y + mOffset.y
			, rightBottom.x
			, rightBottom.y);

			SelectObject(hdc, oldBrush);
			SelectObject(hdc, oldPen);

			DeleteObject(greenPen);
		}
	}

	void CircleCollider2D::Release()
	{
		
	}
}
