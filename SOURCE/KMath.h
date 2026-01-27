#pragma once

namespace KMath
{
	struct Vector2
	{
		float x;
		float y;

		Vector2()
			: x(0.f), y(0.f)
		{}

		Vector2(float inX, float inY)
			: x(inX), y(inY)
		{}
	};
}
