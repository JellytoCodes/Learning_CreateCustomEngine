#include "KApplication.h"
#include "KInput.h"
#include "KResources.h"
#include "KTime.h"
#include "KSceneManager.h"
#include "KCollisionManager.h"
#include "KUIManager.h"
#include "KFmod.h"
#include "KGraphicDevice_DX11.h"

namespace KEngine
{
	Application::Application()
		: mHwnd(nullptr), mHdc(nullptr), mBackHdc(nullptr), mBackBuffer(nullptr), mViewSize(0, 0)
	{
		
	}

	Application::~Application()
	{
		
	}

	void Application::CreateApplication(HWND hwnd, LONG width, LONG height)
	{
		mHwnd = hwnd;
		mHdc = GetDC(hwnd);

		RECT rect = {0, 0, width, height};

		mViewSize.width = rect.right - rect.left;
		mViewSize.height = rect.bottom - rect.top;

		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

		SetWindowPos(mHwnd, nullptr, 0, 0, mViewSize.width, mViewSize.height, 0);
		ShowWindow(mHwnd, true);

		// 윈도우 해상도에 맞는 백버퍼 생성
		mBackBuffer = CreateCompatibleBitmap(mHdc, width, height);

		// 백버퍼를 가르킬 DC 생성
		mBackHdc = CreateCompatibleDC(mHdc);

		HBITMAP oldBitmap = (HBITMAP)SelectObject(mBackHdc, mBackBuffer);
		DeleteObject(oldBitmap);
	}

	void Application::Initialize()
	{
		GraphicDevice_DX11::getInstance().Initialize();

		Fmod::Initialize();
		CollisionManager::Initialize();
		UIManager::Initialize();
		SceneManager::Initialize();

		Input::Initialize();
		Time::Initialize();
	}

	void Application::Run()
	{
		Update();
		LateUpdate();
		Render();
		
		Destroy();
	}

	void Application::Update()
	{
		Input::Update();
		Time::Update();

		CollisionManager::Update();
		UIManager::Update();
		SceneManager::Update();
	}

	void Application::LateUpdate()
	{
		CollisionManager::LateUpdate();
		UIManager::LateUpdate();
		SceneManager::LateUpdate();
	}

	void Application::Render()
	{
		// ClearRenderTarget();

		GraphicDevice_DX11::getInstance().Draw();

		Time::Render();
		CollisionManager::Render();
		UIManager::Render();
		SceneManager::Render();

		// CopyRenderTarget();
	}

	void Application::Release()
	{
		UIManager::Release();
		SceneManager::Release();
		Resources::Release();
	}

	void Application::Destroy()
	{
		SceneManager::Destroy();
	}

	void Application::ClearRenderTarget()
	{
		HBRUSH grayBrush = CreateSolidBrush(RGB(128, 128, 128));
		HBRUSH oldBrush = (HBRUSH)SelectObject(mBackHdc, grayBrush);

		::Rectangle(mBackHdc, -1, -1, mViewSize.width + 1, mViewSize.height + 1);

		SelectObject(mBackHdc, oldBrush);
		DeleteObject(grayBrush);
	}

	void Application::CopyRenderTarget()
	{
		// BackBuffer에 있는걸 원본 Buffer에 복사
		BitBlt(mHdc, 0, 0, mViewSize.width, mViewSize.height, mBackHdc, 0, 0, SRCCOPY);
	}
}

