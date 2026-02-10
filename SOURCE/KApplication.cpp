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
		: mHwnd(nullptr), mHdc(nullptr), mBackHdc(nullptr), mBackBuffer(nullptr), mViewSize(0, 0), mbLoaded(false)
	{
		
	}

	Application::~Application()
	{
		
	}

	void Application::CreateApplication(HWND hwnd, LONG width, LONG height)
	{
		mHwnd = hwnd;
		mHdc = GetDC(hwnd);

		RECT rect = { 0, 0, (LONG)width, (LONG)height };
		::AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

		mViewSize.width = rect.right - rect.left;
		mViewSize.height = rect.bottom - rect.top;

		SetWindowPos(hwnd, nullptr, 0, 0, mViewSize.width, mViewSize.height, 0);
		ShowWindow(hwnd, true);
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
		if (mbLoaded == false) mbLoaded = true;

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
		GraphicDevice_DX11::getInstance().ClearRenderTargetView();
		GraphicDevice_DX11::getInstance().ClearDepthStencilView();
		GraphicDevice_DX11::getInstance().BindViewPort();
		GraphicDevice_DX11::getInstance().BindDefaultRenderTarget();

		Time::Render();
		CollisionManager::Render();
		UIManager::Render();
		SceneManager::Render();

		GraphicDevice_DX11::getInstance().Present();
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
}

