#pragma once
#include "CommonInclude.h"
#include "KEntity.h"

namespace KEngine
{
	class UIBase : public Entity
	{
	public :
		UIBase();
		~UIBase();

		
		void			Initialize();			// UI가 로드 되었을 때 초기화 해주는 함수
		void			Update();
		void			LateUpdate();
		void			Render(HDC hdc);

		void			Active();				// UI가 활성화되면 호출되는 함수
		void			InActive();				// UI가 비활성화되면 호출되는 함수

		void			UIClear();				// UI가 사라질 때 호출되는 함수

		virtual void	OnInit();
		virtual void	OnActive();
		virtual void	OnInActive();
		virtual void	OnUpdate();
		virtual void	OnClear();

		eUIType			GetUIType()					{ return mUIType; }

		void			SetFullScreen(bool enable)	{ mbFullScreen = enable; }
		bool			IsFullScreen()				{ return mbFullScreen; };

	private :
		eUIType mUIType;
		bool mbFullScreen;
		bool mbEnabled;
	};
}


