#include "KPlayScene.h"
#include "GameObject.h"
#include "KAnimator.h"
#include "KBoxCollider2D.h"
#include "KCamera.h"
#include "KCat.h"
#include "KCatScript.h"
#include "KCircleCollider2D.h"
#include "KInput.h"
#include "KObject.h"
#include "KPlayerScript.h"
#include "KSceneManager.h"
#include "KTexture.h"
#include "KPlayer.h"
#include "KResources.h"
#include "KRenderer.h"
#include "KCollisionManager.h"
#include "KFloor.h"
#include "KFloorScript.h"
#include "KRigidBody.h"
#include "KTile.h"
#include "KTileMapRenderer.h"
#include "KUIManager.h"
#include "KAudioClip.h"
#include "KAudioListener.h"
#include "KAudioSource.h"
#include "KSpriteRenderer.h"

namespace KEngine
{
	PlayScene::PlayScene()
		: player(nullptr)
	{
		
	}

	PlayScene::~PlayScene()
	{

	}

	void PlayScene::Initialize()
	{
		// Main Camera
		GameObject* camera = KObject::Instantiate<GameObject>(KEngine::eLayerType::None, KMath::Vector2(512.f, 256.f));
		Camera* cameraComp = camera->AddComponent<Camera>();
		KRenderer::mainCamera = cameraComp;

		AudioClip* ac = Resources::Load<AudioClip>(L"BGSound", L"..\\Resources\\Sound\\smw_bonus_game_end.wav");

		// Player
		
		player = KObject::Instantiate<Player>(eLayerType::Player, KMath::Vector2(400.f, 200.f));
		KObject::DontDestroyOnLoad(player);

		PlayerScript* playerScript = player->AddComponent<PlayerScript>();

		BoxCollider2D* boxCollider = player->AddComponent<BoxCollider2D>();
		boxCollider->SetSize(KMath::Vector2(1.f, 1.f));
		boxCollider->SetOffset(KMath::Vector2(-50.f, -50.f));

		//CircleCollider2D* circleCollider = player->AddComponent<CircleCollider2D>();
		//circleCollider->SetOffset(KMath::Vector2(-50.f, -50.f));

		player->AddComponent<AudioListener>();

		Texture* texture = Resources::Find<Texture>(L"Player");
		Animator* animator = player->AddComponent<Animator>();

		// Create Animation By Player
		animator->CreateAnimation(L"Idle", texture, 
		KMath::Vector2(2000.f, 250.f), KMath::Vector2(250.f, 250.f), KMath::Vector2::Zero, 1, 0.2f);
		animator->CreateAnimation(L"GiveWater", texture, 
		KMath::Vector2(0.f, 2000.f), KMath::Vector2(250.f, 250.f), KMath::Vector2::Zero, 12, 0.2f);

		animator->PlayAnimation(L"Idle", false);

		animator->GetCompleteEvent(L"GiveWater") = std::bind(&PlayerScript::AttackEffect, playerScript);
		player->AddComponent<RigidBody>();

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

	void PlayScene::Render()
	{
		Scene::Render();
	}

	void PlayScene::OnEnter()
	{
		Scene::OnEnter();

		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Animal, true);
		CollisionManager::CollisionLayerCheck(eLayerType::Floor, eLayerType::Player, true);

		UIManager::Push(eUIType::Button);
	}

	void PlayScene::OnExit()
	{
		UIManager::Pop(eUIType::Button);

		Scene::OnExit();
	}
}
