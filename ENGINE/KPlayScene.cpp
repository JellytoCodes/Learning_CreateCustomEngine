#include "KPlayScene.h"
#include "GameObject.h"
#include "KPlayer.h"
#include "KSpriteRenderer.h"
#include "KTransform.h"

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
		{
			std::shared_ptr<Player> player  = std::make_shared<Player>();
			std::shared_ptr<Transform> tr = player->AddComponent<Transform>();
			tr->SetPosition(KMath::Vector2(0, 0));

			tr->SetName(L"TR");

			std::shared_ptr<SpriteRenderer> sr = player->AddComponent<SpriteRenderer>();
			sr->SetName(L"SR");
			sr->LoadImage(L"D:\\Dev\\Programming_Study\\Learning_CreateCustomEngine\\KakaoTalk_20251211_004616658_01.png");

			AddGameObject(player);
		}
	}

	void PlayScene::Update()
	{
		Scene::Update();
	}

	void PlayScene::LateUpdate()
	{
		Scene::LateUpdate();
	}

	void PlayScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
}
