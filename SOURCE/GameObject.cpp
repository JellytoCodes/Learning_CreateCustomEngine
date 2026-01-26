#include "GameObject.h"

namespace KEngine
{
	GameObject::GameObject()
	{

	}

	GameObject::~GameObject()
	{

	}

	void GameObject::Update()
	{
		if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		{
			mPos.x -= 0.01f;
		}
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		{
			mPos.x += 0.01f;
		}
		if (GetAsyncKeyState(VK_UP) & 0x8000)
		{
			mPos.y -= 0.01f;
		}
		if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		{
			mPos.y += 0.01f;
		}
	}

	void GameObject::LateUpdate()
	{

	}

	void GameObject::Render(HDC hdc)
	{
    	// DC(Device Context)란 화면에 출력에 필요한 모든 정보(폰트, 선의 굵기, 색상 등을 어떻게 그려줄 것인지)를 
        // 가지는 데이터 구조체이며 GDI모듈에 의해 관리된다.
        // 화면 출력에 필요한 모든 경우는 WINAPI에서는 DC를 통해서 작업을 진행할 수 있다.

        // 도형 컬러 생성
        {
			HBRUSH blueBrush = CreateSolidBrush(RGB(0, 0, 255));
            HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, blueBrush);
			float left = 100 + mPos.x;
			float top = 100 + mPos.y;
			float right = 200 + mPos.x;
			float bottom = 200 + mPos.y;
            Rectangle(hdc, (int)left, (int)top, (int)right, (int)bottom);    

            SelectObject(hdc, oldBrush);
            DeleteObject(blueBrush);

            HPEN redPen = CreatePen(PS_DOT, 3, RGB(255, 0, 0));
            HPEN oldPen = (HPEN)SelectObject(hdc, redPen);

			Ellipse(hdc, 200, 200, 300, 300);

            SelectObject(hdc, oldPen);
            DeleteObject(redPen);

            HBRUSH grayBrush = (HBRUSH)GetStockObject(GRAY_BRUSH);
            oldBrush = (HBRUSH)SelectObject(hdc, grayBrush);

            Rectangle(hdc, 300, 300, 400, 400);

            SelectObject(hdc, oldBrush);
        }
	}

	void GameObject::SetPosition(float x, float y)
	{
		mPos.x = x;
		mPos.y = y;
	}
}
