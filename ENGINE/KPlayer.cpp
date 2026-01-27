#include "KPlayer.h"

#include "KInput.h"
#include "KTime.h"
#include "KTransform.h"

namespace KEngine
{
	void Player::Initialize()
	{
		GameObject::Initialize();
	}

	void Player::Update()
	{
		GameObject::Update();
	}

	void Player::LateUpdate()
	{
		GameObject::LateUpdate();

		if (Input::GetKeyPressed(eKeyCode::Right))
		{
			std::shared_ptr<Transform> tr = GetComponent<Transform>();
			KMath::Vector2 pos = tr->GetPosition();
			pos.x += 100.f * Time::DeltaTime();
			tr->SetPosition(pos);
		}
	}

	void Player::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}
