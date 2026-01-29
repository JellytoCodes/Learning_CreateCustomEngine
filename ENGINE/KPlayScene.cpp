#include "KPlayScene.h"
#include "GameObject.h"
#include "KCamera.h"
#include "KInput.h"
#include "KObject.h"
#include "KPlayer.h"
#include "KPlayerScript.h"
#include "KSceneManager.h"
#include "KSpriteRenderer.h"
#include "KTexture.h"
#include "KTransform.h"
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
		{
			std::shared_ptr<GameObject> camera = KObject::Instantiate<GameObject>(KEngine::eLayerType::None, KMath::Vector2(512.f, 256.f));
			auto cameraComp = camera->AddComponent<Camera>();
			KRenderer::mainCamera = cameraComp;

			// camera->AddComponent<PlayerScript>();
		}

		// Player
		{
			player = KObject::Instantiate<GameObject>(KEngine::eLayerType::Player, KMath::Vector2(800.f, 270.f));
			std::shared_ptr<SpriteRenderer> sr = player->AddComponent<SpriteRenderer>();
			
			sr->SetSize(KMath::Vector2(0.5f, 0.5f));
			sr->SetTexture(Resources::Find<KEngine::Texture>(L"Ori"));
			
			player->AddComponent<PlayerScript>();
		}
		
		// Background
		{
			auto background = KObject::Instantiate<GameObject>(KEngine::eLayerType::BackGround);
			std::shared_ptr<SpriteRenderer> sr = background->AddComponent<SpriteRenderer>();

			sr->SetTexture(Resources::Find<KEngine::Texture>(L"Map"));
			
			// player->AddComponent<PlayerScript>();
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
