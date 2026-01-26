#include "KApplication.h"

namespace KEngine
{
	Application::Application()
		: mHwnd(nullptr), mHdc(nullptr), mSpeed(0.f), mX(0.f), mY(0.f)
	{
		
	}

	Application::~Application()
	{

	}

	void Application::Initialize(HWND hwnd)
	{
		mHwnd = hwnd;
		mHdc = GetDC(hwnd);
	}

	void Application::Run()
	{
		Update();
		LateUpdate();
		Render();
	}

	void Application::Update()
	{
		if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		{
			mX -= 0.005f;
		}
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		{
			mX += 0.005f;
		}
		if (GetAsyncKeyState(VK_UP) & 0x8000)
		{
			mY -= 0.005f;
		}
		if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		{
			mY += 0.005f;
		}
	}

	void Application::LateUpdate()
	{
		
	}

	void Application::Render()
	{
    	// DC(Device Context)란 화면에 출력에 필요한 모든 정보(폰트, 선의 굵기, 색상 등을 어떻게 그려줄 것인지)를 
        // 가지는 데이터 구조체이며 GDI모듈에 의해 관리된다.
        // 화면 출력에 필요한 모든 경우는 WINAPI에서는 DC를 통해서 작업을 진행할 수 있다.

        // 도형 컬러 생성
        {
			HBRUSH blueBrush = CreateSolidBrush(RGB(0, 0, 255));
            HBRUSH oldBrush = (HBRUSH)SelectObject(mHdc, blueBrush);
            Rectangle(mHdc, 100 + mX, 100 + mY, 200 + mX, 200 + mY);    

            SelectObject(mHdc, oldBrush);
            DeleteObject(blueBrush);

            HPEN redPen = CreatePen(PS_DOT, 3, RGB(255, 0, 0));
            HPEN oldPen = (HPEN)SelectObject(mHdc, redPen);

			Ellipse(mHdc, 200, 200, 300, 300);

            SelectObject(mHdc, oldPen);
            DeleteObject(redPen);

            HBRUSH grayBrush = (HBRUSH)GetStockObject(GRAY_BRUSH);
            oldBrush = (HBRUSH)SelectObject(mHdc, grayBrush);

            Rectangle(mHdc, 300, 300, 400, 400);

            SelectObject(mHdc, oldBrush);
        }
	}

}

