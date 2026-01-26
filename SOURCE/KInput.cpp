#include "KInput.h"

namespace KEngine
{
	std::vector<Key> Input::mKeys = { };

	int ASCII[(UINT)eKeyCode::End] =
	{
		'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',
		'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L',
		'Z', 'X', 'C', 'V', 'B', 'N', 'M',
	};

	void Input::Initialize()
	{
		mKeys.resize((UINT)eKeyCode::End);



		for (size_t i = 0 ; i < (UINT)eKeyCode::End ; i++)
		{
			Key key = {};
			key.bPressed = false;
			key.state = eKeyState::None;
			key.keyCode = (eKeyCode)i;

			mKeys.push_back(key);
		}
	}

	void Input::Update()
	{
		for (size_t i = 0 ; i < mKeys.size() ; i++)
		{
			if (GetAsyncKeyState(ASCII[i]) & 0x8000)	// 키가 눌림
			{
				if (mKeys[i].bPressed == true)	mKeys[i].state = eKeyState::Pressed;
				else							mKeys[i].state = eKeyState::Down;
				
				mKeys[i].bPressed = true;
			}
			else										// 키가 안눌림
			{
				// 이전 프레임에 눌려져 있었을 경우
				if (mKeys[i].bPressed == true)	mKeys[i].state = eKeyState::Up;
				// 이전 프레임도 지금도 눌려있지 않은 경우
				else							mKeys[i].state = eKeyState::None;
				
				mKeys[i].bPressed = false;				
			}
		}
	}
}
