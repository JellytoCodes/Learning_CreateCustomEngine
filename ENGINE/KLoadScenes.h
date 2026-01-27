#pragma once

#include "../SOURCE/KSceneManager.h"

#include "KPlayScene.h"
#include "KTitleScene.h"


namespace KEngine
{
	void LoadScenes()
	{
		SceneManager::CreateScene<TitleScene>(L"TitleScene");
		SceneManager::CreateScene<PlayScene>(L"PlayScene");

		SceneManager::LoadScene(L"PlayScene");
	}
}
