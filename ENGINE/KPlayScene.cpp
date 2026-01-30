#include "KPlayScene.h"
#include "GameObject.h"
#include "KAnimator.h"
#include "KCamera.h"
#include "KCat.h"
#include "KCatScript.h"
#include "KInput.h"
#include "KObject.h"
#include "KPlayerScript.h"
#include "KSceneManager.h"
#include "KTexture.h"
#include "KPlayer.h"
#include "KResources.h"
#include "KRenderer.h"

namespace KEngine
{
	PlayScene::PlayScene()
	{
		
	}

	PlayScene::~PlayScene()
	{

	}

	void PlayScene::Initialize()
	{
		// Main Camera
		std::shared_ptr<GameObject> camera = KObject::Instantiate<GameObject>(KEngine::eLayerType::None, KMath::Vector2(512.f, 256.f));
		auto cameraComp = camera->AddComponent<Camera>();
		KRenderer::mainCamera = cameraComp;

		// Player
		{
			player = KObject::Instantiate<Player>(KEngine::eLayerType::Player, KMath::Vector2(0.f, 0.f));
			auto playerScript = player->AddComponent<PlayerScript>();

			auto texture = Resources::Find<KEngine::Texture>(L"Player");
			auto animator = player->AddComponent<Animator>();

			// Create Animation By Player
			animator->CreateAnimation(L"Idle", texture, 
			KMath::Vector2(2000.f, 250.f), KMath::Vector2(250.f, 250.f), KMath::Vector2::Zero, 1, 0.2f);
			animator->CreateAnimation(L"GiveWater", texture, 
			KMath::Vector2(0.f, 2000.f), KMath::Vector2(250.f, 250.f), KMath::Vector2::Zero, 12, 0.2f);

			animator->PlayAnimation(L"Idle", false);

			animator->GetCompleteEvent(L"GiveWater") = std::bind(&PlayerScript::AttackEffect, playerScript.get());

			player->GetComponent<Transform>()->SetPosition(KMath::Vector2(100.f, 100.f));
		}

		// Cat
		{
			auto cat = KObject::Instantiate<Cat>(KEngine::eLayerType::Animal);
			cat->AddComponent<CatScript>();
			cameraComp->SetTarget(cat);

			auto texture = Resources::Find<KEngine::Texture>(L"Cat");
			auto animator = cat->AddComponent<Animator>();

			// Create Animation By Cat
			animator->CreateAnimation(L"DownWalk", texture, 
			KMath::Vector2(0.f, 0.f), KMath::Vector2(32.f, 32.f), KMath::Vector2::Zero, 4, 0.2f);
			animator->CreateAnimation(L"RightWalk", texture, 
			KMath::Vector2(0.f, 32.f), KMath::Vector2(32.f, 32.f), KMath::Vector2::Zero, 4, 0.2f);
			animator->CreateAnimation(L"UpWalk", texture, 
			KMath::Vector2(0.f, 64.f), KMath::Vector2(32.f, 32.f), KMath::Vector2::Zero, 4, 0.2f);
			animator->CreateAnimation(L"LeftWalk", texture, 
			KMath::Vector2(0.f, 96.f), KMath::Vector2(32.f, 32.f), KMath::Vector2::Zero, 4, 0.2f);
			animator->CreateAnimation(L"SitDown", texture, 
			KMath::Vector2(0.f, 128.f), KMath::Vector2(32.f, 32.f), KMath::Vector2::Zero, 4, 0.2f);
			animator->CreateAnimation(L"Grooming", texture, 
			KMath::Vector2(0.f, 160.f), KMath::Vector2(32.f, 32.f), KMath::Vector2::Zero, 4, 0.2f);
			animator->CreateAnimation(L"LayDown", texture, 
			KMath::Vector2(0.f, 192.f), KMath::Vector2(32.f, 32.f), KMath::Vector2::Zero, 4, 0.2f);

			animator->PlayAnimation(L"SitDown", false);

			cat->GetComponent<Transform>()->SetPosition(KMath::Vector2(200.f, 200.f));
			cat->GetComponent<Transform>()->SetScale(KMath::Vector2(2.f, 2.f));
		}


		Scene::Initialize();
	}

	void PlayScene::Update()
	{
		Scene::Update();
	}

	void PlayScene::LateUpdate()
	{
		Scene::LateUpdate();

		if (Input::GetKeyDown(eKeyCode::N))
		{
			SceneManager::LoadScene(L"TitleScene");
		}
	}

	void PlayScene::Render(HDC hdc)
	{
		Scene::Render(hdc);

		std::wstring str = L"Play Scene ";
		TextOut(hdc, 0, 0, str.c_str(), (int)str.length());
	}

	void PlayScene::OnEnter()
	{
		Scene::OnEnter();

	}

	void PlayScene::OnExit()
	{
		Scene::OnExit();
	}
}
