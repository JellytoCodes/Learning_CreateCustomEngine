#pragma once
#include "KResource.h"
#include "KTexture.h"

namespace KEngine
{
	class Animator;

	class Animation : public Resource
	{
		using Super = Resource;
	public :
		struct Sprite
		{
			KMath::Vector2 leftTop;
			KMath::Vector2 size;
			KMath::Vector2 offset;
			float duration;
			Sprite()
				: leftTop(KMath::Vector2::Zero), size(KMath::Vector2::Zero), offset(KMath::Vector2::Zero), duration(0) { }
		};

		Animation();
		~Animation();

		HRESULT Load(const std::wstring& path) override;

		void Update();

		void Render();

		void CreateAnimation(
		const std::wstring& name,			// 애니메이션 이름
			Texture* spriteSheet,			// 사용할 애니메이션 스프라이트
			KMath::Vector2 leftTop,			// 시트 내 사용할 애니메이션의 좌표
			KMath::Vector2 size,			// 애니메이션 프레임 사이즈
			KMath::Vector2 offset,			// 프레임 사이즈가 안맞을 때 맞춰주기 위한 목적
			UINT spriteLength,				// 애니메이션의 총 프레임
			float duration					// 프레임 전환 시간 (재생 속도)
			);

		void Reset();

		bool IsComplete() { return mbComplete; }
		void SetAnimator(Animator* animator) { mAnimator = animator; }

	private :
		Animator*					mAnimator;
		Texture*					mTexture;

		std::vector<Sprite>			mAnimationSheet;
		int							mIndex;
		float						mTime;
		bool						mbComplete;
	};
}
