#include "KCamera.h"

#include "GameObject.h"
#include "KTransform.h"
#include "KApplication.h"

extern KEngine::Application application;

namespace KEngine
{
	Camera::Camera()
		: Super(eComponentType::Camera),
		mDistance(KMath::Vector2::Zero), mResolution(KMath::Vector2::Zero), mLookPosition(KMath::Vector2::Zero), mTarget(nullptr)
	{
		
	}

	Camera::~Camera()
	{

	}

	void Camera::Initialize()
	{
		mResolution.x = (float)application.GetViewSize().width;
		mResolution.y = (float)application.GetViewSize().height;
	}

	void Camera::Update()
	{
		if (mTarget)
		{
			Transform* transform = mTarget->GetComponent<Transform>();
			mLookPosition = transform->GetPosition();
		}
		else
		{
			Transform* cameraTransform = GetOwner()->GetComponent<Transform>();
			mLookPosition = cameraTransform->GetPosition();
		}

		mDistance = mLookPosition - (mResolution / 2.f); 
	}

	void Camera::LateUpdate()
	{
		
	}

	void Camera::Render()
	{
		
	}

	void Camera::Release()
	{
		
	}
}
