#include "KInput.h"
#include "algorithm"
#include "KApplication.h"

extern KEngine::Application application;

namespace KEngine
{
	std::vector<Key> Input::mKeys = { };
	KMath::Vector2 Input::mMousePosition = KMath::Vector2::Zero;

	int ASCII[(UINT)eKeyCode::End] =
	{
		'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',
		'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L',
		'Z', 'X', 'C', 'V', 'B', 'N', 'M',
		VK_LEFT, VK_RIGHT, VK_DOWN, VK_UP,
		VK_LBUTTON, VK_RBUTTON, VK_MBUTTON
	};

	void Input::Initialize()
	{
		CreateKeys();
	}

	void Input::Update()
	{
		UpdateKeys();
	}

	void Input::CreateKeys()
	{
		for (size_t i = 0 ; i < (UINT)eKeyCode::End ; i++)
		{
			Key key = { };
			key.bPressed = false;
			key.state = eKeyState::None;
			key.keyCode = (eKeyCode)i;

			mKeys.push_back(key);
		}
	}

	void Input::UpdateKeys()
	{
		std::for_each(mKeys.begin(), mKeys.end(),
		[](Key& key)
		{
			UpdateKey(key);
		});
	}

	void Input::UpdateKey(Key& key)
	{
		// 현재 윈도우를 포커싱중인지 체크
		if (GetFocus())
		{
			if (IsKeyDown(key.keyCode))		UpdateKeyDown(key);
			else							UpdateKeyUp(key);

			GetMousePositionByWindow();
		}
		else
		{
			ClearKeys();
		}
	}

	bool Input::IsKeyDown(eKeyCode code)
	{
		return GetAsyncKeyState(ASCII[(UINT)code]) & 0x8000;
	}

	void Input::UpdateKeyDown(Key& key)
	{
		if (key.bPressed == true)		key.state = eKeyState::Pressed;
		else							key.state = eKeyState::Down;

		key.bPressed = true;
	}

	void Input::UpdateKeyUp(Key& key)
	{
		if (key.bPressed == true)		key.state = eKeyState::Up;
		else							key.state = eKeyState::None;

		key.bPressed = false;
	}

	void Input::GetMousePositionByWindow()
	{
		POINT mousePos;

		// LP = 해당 자료형의 포인터
		GetCursorPos(&mousePos);
		ScreenToClient(application.GetHwnd(), &mousePos);

		UINT width = application.GetViewSize().width;
		UINT height = application.GetViewSize().height;

		mMousePosition.x = -1.f;
		mMousePosition.y = -1.f;

		if (mousePos.x < width && mousePos.x >= 0 && mousePos.y < height && mousePos.y >= 0)
		{
			mMousePosition.x = (float)mousePos.x;
			mMousePosition.y = (float)mousePos.y;
		}


	}

	void Input::ClearKeys()
	{
		for (Key& key : mKeys)
		{
			if (key.state == eKeyState::Down || key.state == eKeyState::Pressed)	key.state = eKeyState::Up;
			else if (key.state == eKeyState::Up)									key.state = eKeyState::None;

			key.bPressed = false;
		}
	}
}
