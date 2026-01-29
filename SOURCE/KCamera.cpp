#include "KCamera.h"

#include "GameObject.h"
#include "KTransform.h"
#include "KApplication.h"

extern KEngine::Application application;

namespace KEngine
{
	Camera::Camera()
		: Super(eComponentType::Camera),
		mDistance(KMath::Vector2::Zero), mResolution(KMath::Vector2::Zero), mLookPosition(KMath::Vector2::Zero)
	{
		
	}

	Camera::~Camera()
	{

	}

	void Camera::Initialize()
	{
		mResolution.x = application.GetViewSize().width;
		mResolution.y = application.GetViewSize().height;
	}

	void Camera::Update()
	{
		if (auto target = mTarget.lock())
		{
			auto transform = target->GetComponent<Transform>();
			mLookPosition = transform->GetPosition();
		}

		auto cameraTransform = GetOwner().lock()->GetComponent<Transform>();
		mLookPosition = cameraTransform->GetPosition();

		mDistance = mLookPosition - (mResolution / 2.f); 
	}

	void Camera::LateUpdate()
	{
		
	}

	void Camera::Render(HDC hdc)
	{
		
	}

	void Camera::Release()
	{
		
	}
}
