#include "KTime.h"
#include "string"
namespace KEngine
{
	LARGE_INTEGER Time::mCpuFrequency		= {};
	LARGE_INTEGER Time::mPrevFrequency		= {};
	LARGE_INTEGER Time::mCurrentFrequency	= {};

	float Time::deltaTime					= 0.f;

	void Time::Initialize()
	{
		// CPU 고유 진동 수
		QueryPerformanceFrequency(&mCpuFrequency);

		// 프로그램이 시작 했을 때 현재 진동 수
		QueryPerformanceCounter(&mPrevFrequency);
	}

	void Time::Update()
	{
		QueryPerformanceCounter(&mCurrentFrequency);

		float differenceFrequency = static_cast<float>(mCurrentFrequency.QuadPart - mPrevFrequency.QuadPart);

		deltaTime = differenceFrequency / static_cast<float>(mCpuFrequency.QuadPart);

		mPrevFrequency.QuadPart = mCurrentFrequency.QuadPart;
	}

	void Time::Render(HDC hdc)
	{
		static float time = 0.f;
		time += deltaTime;

		float fps = 1.f / deltaTime;

		std::wstring fpsStr = L"FPS : " + std::to_wstring((UINT)fps);
		std::wstring timeStr = L"Time : " + std::to_wstring((UINT)time);

		TextOut(hdc, 0, 0, fpsStr.c_str(), (int)fpsStr.length());
		TextOut(hdc, 0, 20, timeStr.c_str(), (int)timeStr.length());
	}
}
