#include "KTitleScene.h"

#include "KInput.h"
#include "KSceneManager.h"

namespace KEngine
{
	TitleScene::TitleScene()
	{
	}

	TitleScene::~TitleScene()
	{
	}

	void TitleScene::Initialize()
	{
		Scene::Initialize();
	}

	void TitleScene::Update()
	{
		Scene::Update();
	}

	void TitleScene::LateUpdate()
	{
		Scene::LateUpdate();

		if (Input::GetKeyDown(eKeyCode::N))
		{
			SceneManager::LoadScene(L"PlayScene");
		}
	}

	void TitleScene::Render(HDC hdc)
	{
		Scene::Render(hdc);

		std::wstring str = L"Title Scene ";
		TextOut(hdc, 0, 0, str.c_str(), (int)str.length());
	}
}
