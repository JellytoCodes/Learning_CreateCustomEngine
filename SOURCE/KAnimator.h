#pragma once
#include "CommonInclude.h"
#include "KComponent.h"
#include "KAnimation.h"

namespace KEngine
{
	class Texture;

	class Animator : public Component
	{
		using Super = Component;

	public :
		struct Event
		{
			void operator=(std::function<void()> func)
			{
				mEvent = std::move(func);
			}
			void operator()()
			{
				if (mEvent) mEvent();
			}

			std::function<void()> mEvent;
		};

		struct Events
		{
			Event startEvent;
			Event completeEvent;
			Event endEvent;	
		};

		Animator();
		~Animator();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;
		void Release() override;

		void CreateAnimation(
			const std::wstring& name,					// 애니메이션 이름
			Texture* spriteSheet,		// 사용할 애니메이션 스프라이트
			KMath::Vector2 leftTop,						// 시트 내 사용할 애니메이션의 좌표
			KMath::Vector2 size,						// 애니메이션 프레임 사이즈
			KMath::Vector2 offset,						// 프레임 사이즈가 안맞을 때 맞춰주기 위한 목적
			UINT spriteLength,							// 애니메이션의 총 프레임
			float duration								// 프레임 전환 시간 (재생 속도)
			);

		void CreateAnimationByFolder();

		Animation* FindAnimation(const std::wstring& name);
		void PlayAnimation(const std::wstring& name, bool loop = true);

		Events* FindEvents(const std::wstring& name);

		std::function<void()>& GetStartEvent(const std::wstring& name);
		std::function<void()>& GetCompleteEvent(const std::wstring& name);
		std::function<void()>& GetEndEvent(const std::wstring& name);

		bool IsComplete() { return mActiveAnimation->IsComplete(); }

	private :
		std::map<std::wstring, std::unique_ptr<Animation>> mAnimations;
		Animation* mActiveAnimation;

		bool mbLoop;

		// Event
		std::map<std::wstring, std::unique_ptr<Events>> mEvents;
	};
}
