#pragma once
#include "CommonInclude.h"

namespace KEngine
{
	enum class eKeyState
	{
		Down,
		Pressed,
		Up,
		None,
	};

	enum class eKeyCode
	{
		Q, W, E, R, T, Y, U, I, O, P,
		A, S, D, F, G, H, J, K, L,
		Z, X, C, V, B, N, M,
		Left, Right, Down, Up,
		LButton, RButton, MButton,		// Mouse
		End,
	};

	struct Key
	{
		eKeyCode keyCode;
		eKeyState state;
		bool bPressed;
	};

	class Input
	{
	public :
		static void Initialize();
		static void Update();

		__forceinline static bool GetKeyDown(eKeyCode code)		{ return mKeys[(UINT)code].state == eKeyState::Down; }
		__forceinline static bool GetKeyPressed(eKeyCode code)	{ return mKeys[(UINT)code].state == eKeyState::Pressed; }
		__forceinline static bool GetKeyUp(eKeyCode code)		{ return mKeys[(UINT)code].state == eKeyState::Up; }

		static KMath::Vector2 GetMousePosition() { return mMousePosition; }

	private :
		static void CreateKeys();
		static void UpdateKeys();
		static void UpdateKey(Key& key);

		static bool IsKeyDown(eKeyCode code);
		static void UpdateKeyDown(Key& key);
		static void UpdateKeyUp(Key& key);
		static void GetMousePositionByWindow();
		static void ClearKeys();

		static std::vector<Key> mKeys;
		static KMath::Vector2 mMousePosition;
	};	
}


