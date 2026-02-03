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
#include "KRigidBody.h"
#include "KTile.h"
#include "KTileMapRenderer.h"

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

		// Tile Map
		{
			FILE* pFile = nullptr;
			_wfopen_s(&pFile, L"..\\Resources\\Home", L"rb");
			
			while (true)
			{
				int idxX = 0;
				int idxY = 0;

				int posX = 0;
				int posY = 0;


				if (fread(&idxX, sizeof(int), 1, pFile) == NULL)
					break;
				if (fread(&idxY, sizeof(int), 1, pFile) == NULL)
					break;
				if (fread(&posX, sizeof(int), 1, pFile) == NULL)
					break;
				if (fread(&posY, sizeof(int), 1, pFile) == NULL)
					break;

				Tile* tile = KObject::Instantiate<Tile>(eLayerType::Tile, KMath::Vector2(posX, posY));
				TileMapRenderer* tmr = tile->AddComponent<TileMapRenderer>();
				tmr->SetTexture(Resources::Find<Texture>(L"SpringFloor"));
				tmr->SetIndex(KMath::Vector2(idxX, idxY));

				//mTiles.push_back(tile);
			}

			fclose(pFile);
		}

		// Player
		{
			player = KObject::Instantiate<Player>(KEngine::eLayerType::Player, KMath::Vector2(400.f, 200.f));

			KObject::DontDestroyOnLoad(player);

			auto playerScript = player->AddComponent<PlayerScript>();
			//BoxCollider2D* boxCollider = player->AddComponent<BoxCollider2D>();
			//boxCollider->SetBoxSize(KMath::Vector2(50.f, 50.f));
			//boxCollider->SetOffset(KMath::Vector2(-50.f, -50.f));
			CircleCollider2D* circleCollider = player->AddComponent<CircleCollider2D>();
			circleCollider->SetOffset(KMath::Vector2(-50.f, -50.f));

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
		}

		// Cat
		/*{
			Cat* cat = KObject::Instantiate<Cat>(KEngine::eLayerType::Animal);
			CatScript* catSrc = cat->AddComponent<CatScript>();

			Texture* texture = Resources::Find<KEngine::Texture>(L"Cat");
			Animator* animator = cat->AddComponent<Animator>();

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

			cat->GetComponent<Transform>()->SetPosition(KMath::Vector2(100.f, 100.f));
			cat->GetComponent<Transform>()->SetScale(KMath::Vector2(2.f, 2.f));

			KMath::Vector2 mousePosition = Input::GetMousePosition();
			catSrc->SetDest(mousePosition);
		}*/

		// Mushroom
		{
			Cat* mushroom = KObject::Instantiate<Cat>(KEngine::eLayerType::Animal);
			mushroom->AddComponent<CatScript>();
			BoxCollider2D* boxCollider = mushroom->AddComponent<BoxCollider2D>();
			boxCollider->SetBoxSize(KMath::Vector2(50.f, 50.f));
			boxCollider->SetOffset(KMath::Vector2(-50.f, -50.f));

			//CircleCollider2D* circleCollider = mushroom->AddComponent<CircleCollider2D>();
			//circleCollider->SetOffset(KMath::Vector2(-50.f, -50.f));

			Animator* animator = mushroom->AddComponent<Animator>();

			animator->CreateAnimationByFolder(L"MushroomIdle", L"..\\Resources\\Mushroom", KMath::Vector2::Zero, 0.1f);
			animator->PlayAnimation(L"MushroomIdle");

			mushroom->GetComponent<Transform>()->SetPosition(KMath::Vector2(200.f, 200.f));
			mushroom->GetComponent<Transform>()->SetScale(KMath::Vector2(1.f, 1.f));
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

		std::wstring str = L"Play Scene";
		TextOut(hdc, 0, 0, str.c_str(), (int)str.length());
	}

	void PlayScene::OnEnter()
	{
		Scene::OnEnter();

		CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Animal, true);
	}

	void PlayScene::OnExit()
	{
		Scene::OnExit();
	}
}
