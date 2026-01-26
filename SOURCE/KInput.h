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

		static bool GetKeyDown(eKeyCode code)		{ return mKeys[(UINT)code].state == eKeyState::Down; }
		static bool GetKeyPressed(eKeyCode code)	{ return mKeys[(UINT)code].state == eKeyState::Pressed; }
		static bool GetKeyUp(eKeyCode code)			{ return mKeys[(UINT)code].state == eKeyState::Up; }

	private :
		static std::vector<Key> mKeys;
	};	
}


