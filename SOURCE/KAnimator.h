#pragma once
#include "CommonInclude.h"
#include "KComponent.h"
#include "KAnimation.h"

namespace KEngine
{
	class Texture;
}

namespace KEngine
{
	class Animator : public Component, public std::enable_shared_from_this<Animator>
	{
		using Super = Component;

	public :
		Animator();
		~Animator();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;
		void Release() override;

		void CreateAnimation(
			const std::wstring& name,					// 애니메이션 이름
			std::shared_ptr<Texture> spriteSheet,		// 사용할 애니메이션 스프라이트
			KMath::Vector2 leftTop,						// 시트 내 사용할 애니메이션의 좌표
			KMath::Vector2 size,						// 애니메이션 프레임 사이즈
			KMath::Vector2 offset,						// 프레임 사이즈가 안맞을 때 맞춰주기 위한 목적
			UINT spriteLength,							// 애니메이션의 총 프레임
			float duration								// 프레임 전환 시간 (재생 속도)
			);

		std::shared_ptr<Animation> FindAnimation(const std::wstring& name);
		void PlayAnimation(const std::wstring& name, bool loop = true);

	private :
		std::map<std::wstring, std::shared_ptr<Animation>> mAnimations;
		std::shared_ptr<Animation> mActiveAnimation;

		bool mbLoop;


	};
}
