#pragma once
#include "CommonInclude.h"
#include "KEntity.h"

namespace KEngine
{
	class UIBase : public Entity
	{
	public :
		UIBase(eUIType type);
		virtual ~UIBase();

		struct Event
		{
			void operator=(std::function<void()> func)
			{
				mEvent = std::move(func);
			}
			void operator()()
			{
				if (mEvent)
					mEvent();
			}
			std::function<void()> mEvent;
		};

		void			Initialize();			// UI가 로드 되었을 때 초기화 해주는 함수
		void			Update();
		void			LateUpdate();
		void			Render();

		void			Active();				// UI가 활성화되면 호출되는 함수
		void			InActive();				// UI가 비활성화되면 호출되는 함수

		void			UIClear();				// UI가 사라질 때 호출되는 함수

		virtual void	OnInit();
		virtual void	OnActive();
		virtual void	OnInActive();
		virtual void	OnUpdate();
		virtual void	OnLateUpdate();
		virtual void	OnRender();
		virtual void	OnClear();

		eUIType			GetUIType() const					{ return mUIType; }
		void			SetUIType(eUIType type)				{ mUIType = type; }

		bool			IsFullScreen() const				{ return mbFullScreen; }
		void			SetFullScreen(bool enable)			{ mbFullScreen = enable; }

		KMath::Vector2	GetPos() const						{ return mPosition; }
		void			SetPos(KMath::Vector2 position)		{ mPosition = position; }

		KMath::Vector2	GetSize() const						{ return mSize; }
		void			SetSize(KMath::Vector2 size)		{ mSize = size; }

	protected :
		KMath::Vector2		mPosition;
		KMath::Vector2		mSize;
		bool				mbMouseOn;

	private :
		eUIType				mUIType;
		bool				mbFullScreen;
		bool				mbEnabled;

		UIBase*				mParent;
	};
}


