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
		// Player
		player = KObject::Instantiate<Player>(eLayerType::Player, KMath::Vector2(400.f, 200.f));
		KObject::DontDestroyOnLoad(player);

		SpriteRenderer* sr = player->AddComponent<SpriteRenderer>();
		sr->SetMaterial(Resources::Find<Material>(L"SpriteMaterial"));
		sr->SetSprite(Resources::Find<Texture>(L"Player"));

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

		GraphicDevice_DX11::getInstance().Draw();
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
