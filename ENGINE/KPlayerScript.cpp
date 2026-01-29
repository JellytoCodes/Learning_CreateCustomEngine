#include "KPlayerScript.h"

#include "KInput.h"
#include "KTime.h"
#include "KTransform.h"
#include "GameObject.h"

namespace KEngine
{
	PlayerScript::PlayerScript()
	{

	}

	PlayerScript::~PlayerScript()
	{

	}

	void PlayerScript::Initialize()
	{
		
	}

	void PlayerScript::Update()
	{
		if (Input::GetKeyPressed(eKeyCode::Right))
		{
			std::shared_ptr<Transform> tr = GetOwner().lock()->GetComponent<Transform>();
			KMath::Vector2 pos = tr->GetPosition();
			pos.x += 100.f * Time::DeltaTime();
			tr->SetPosition(pos);
		}
		if (Input::GetKeyPressed(eKeyCode::Left))
		{
			std::shared_ptr<Transform> tr = GetOwner().lock()->GetComponent<Transform>();
			KMath::Vector2 pos = tr->GetPosition();
			pos.x -= 100.f * Time::DeltaTime();
			tr->SetPosition(pos);
		}
		if (Input::GetKeyPressed(eKeyCode::Up))
		{
			std::shared_ptr<Transform> tr = GetOwner().lock()->GetComponent<Transform>();
			KMath::Vector2 pos = tr->GetPosition();
			pos.y -= 100.f * Time::DeltaTime();
			tr->SetPosition(pos);
		}

		if (Input::GetKeyPressed(eKeyCode::Down))
		{
			std::shared_ptr<Transform> tr = GetOwner().lock()->GetComponent<Transform>();
			KMath::Vector2 pos = tr->GetPosition();
			pos.y += 100.f * Time::DeltaTime();
			tr->SetPosition(pos);
		}
	}

	void PlayerScript::LateUpdate()
	{
		
	}

	void PlayerScript::Render(HDC hdc)
	{
		
	}

	void PlayerScript::Release()
	{
		
	}	
}

