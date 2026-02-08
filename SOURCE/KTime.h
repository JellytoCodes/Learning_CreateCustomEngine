#pragma once
#include "CommonInclude.h"

namespace KEngine
{
	class Time
	{
	public :
		static void Initialize();
		static void Update();
		static void Render();

		__forceinline static float DeltaTime() { return deltaTime; }

	private :
		static LARGE_INTEGER mCpuFrequency;
		static LARGE_INTEGER mPrevFrequency;
		static LARGE_INTEGER mCurrentFrequency;

		static float deltaTime;
	};
}


