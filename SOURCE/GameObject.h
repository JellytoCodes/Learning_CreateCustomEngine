#pragma once
#include "CommonInclude.h"

namespace KEngine
{
	struct Position
	{
		float x;
		float y;
	};

	// 언리얼에서는 Actor
	class GameObject
	{
	public :
		GameObject();
		~GameObject();

		void Update();
		void LateUpdate();
		void Render(HDC hdc);

		void SetPosition(float x, float y);
		Position GetPosition() const		{ return mPos; }

	private :
		Position mPos;
	};	
}