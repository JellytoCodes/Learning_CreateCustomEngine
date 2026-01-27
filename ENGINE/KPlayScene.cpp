#include "KPlayScene.h"
#include "GameObject.h"
#include "KInput.h"
#include "KPlayer.h"
#include "KSceneManager.h"
#include "KSpriteRenderer.h"
#include "KTransform.h"
#include "KTitleScene.h"

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
			player = std::make_shared<Player>();
			std::shared_ptr<Transform> tr = player->AddComponent<Transform>();
			tr->SetPosition(KMath::Vector2(0, 0));
			tr->SetName(L"TR");

			std::shared_ptr<SpriteRenderer> sr = player->AddComponent<SpriteRenderer>();
			sr->SetName(L"SR");
			sr->LoadImage(L"D:\\Dev\\Programming_Study\\Learning_CreateCustomEngine\\KakaoTalk_20251211_004616658_01.png");

			AddGameObject(player, eLayerType::BackGround);	
		}
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
		{
			std::shared_ptr<Transform> tr = player->GetComponent<Transform>();
			tr->SetPosition(KMath::Vector2(0, 0));
		}
	}
}
