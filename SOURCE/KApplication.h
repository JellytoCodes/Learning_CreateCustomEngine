#pragma once
#include "CommonInclude.h"

namespace KEngine
{
	class GraphicDevice_DX11;
}

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

		void		CreateApplication(HWND hwnd, LONG width, LONG height);
		void		Initialize();
		void		Run();

		void		Update();
		void		LateUpdate();
		void		Render();
		void		Release();
		void		Destroy();

		HWND		GetHwnd() const			{ return mHwnd; }
		HDC			GetHdc() const			{ return mHdc; }
		ViewSize	GetViewSize() const		{ return mViewSize; }

		bool		IsLoaded() const		{ return mbLoaded; }
		void		IsLoaded(bool load)		{ mbLoaded = load; }

	private :
		void		ClearRenderTarget();
		void		CopyRenderTarget();

		HWND			mHwnd;
		HDC				mHdc;

		HDC				mBackHdc;
		HBITMAP			mBackBuffer;

		ViewSize		mViewSize;
		bool			mbLoaded;
		//std::unique_ptr<GraphicDevice_DX11>		mGraphicDevice;
	};	
}


