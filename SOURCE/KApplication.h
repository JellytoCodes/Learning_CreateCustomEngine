#pragma once
#include "CommonInclude.h"

struct ViewSize
{
	LONG width;
	LONG height;
};

namespace KEngine
{
	class Scene;

	class Application
	{
	public :
		Application();
		~Application();

		void Initialize(HWND hwnd, LONG width, LONG height);
		void Run();

		void Update();
		void LateUpdate();
		void Render();
		void Release();

		HDC GetHdc() { return mHdc; }
		ViewSize GetViewSize() { return mViewSize; }

	private :
		void ClearRenderTarget();
		void CopyRenderTarget();
		HWND mHwnd;
		HDC mHdc;

		HDC mBackHdc;
		HBITMAP mBackBuffer;

		ViewSize mViewSize;

		std::vector<std::shared_ptr<Scene>> mScenes;
		
	};	
}


