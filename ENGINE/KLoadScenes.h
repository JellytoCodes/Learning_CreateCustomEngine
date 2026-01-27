#pragma once
#include "KPlayScene.h"
#include "../SOURCE/KSceneManager.h"

namespace KEngine
{
	void LoadScenes()
	{
		SceneManager::CreateScene<PlayScene>(L"PlayScene");

		SceneManager::LoadScene(L"PlayScene");
	}
}
