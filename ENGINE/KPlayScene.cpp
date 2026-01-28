#include "KPlayScene.h"
#include "GameObject.h"
#include "KInput.h"
#include "KObject.h"
#include "KPlayer.h"
#include "KSceneManager.h"
#include "KSpriteRenderer.h"
#include "KTexture.h"
#include "KTransform.h"
#include "KResources.h"
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
		// 게임오브젝트 만들기전에 리소스들 전부 Load
		

		{
			bg = KObject::Instantiate<Player>(KEngine::eLayerType::BackGround, KMath::Vector2(100.f, 100.f));
			std::shared_ptr<SpriteRenderer> sr = bg->AddComponent<SpriteRenderer>();
			sr->SetTexture(Resources::Find<KEngine::Texture>(L"BG"));

			//std::shared_ptr<KEngine::Texture> texture = std::make_shared<KEngine::Texture>();
			//texture->Load(L"D:\\Dev\\Programming_Study\\Learning_CreateCustomEngine\\KakaoTalk_20251211_004616658_01.png");
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
		{
			std::shared_ptr<Transform> tr = bg->GetComponent<Transform>();
			tr->SetPosition(KMath::Vector2(0, 0));
		}
	}
}
