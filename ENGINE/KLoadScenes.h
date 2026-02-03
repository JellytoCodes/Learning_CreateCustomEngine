#pragma once

#include "../SOURCE/KSceneManager.h"

#include "KPlayScene.h"
#include "KTitleScene.h"
#include "KToolScene.h"

namespace KEngine
{
	void LoadScenes()
	{
		SceneManager::CreateScene<TitleScene>(L"TitleScene");
		SceneManager::CreateScene<PlayScene>(L"PlayScene");
		SceneManager::CreateScene<ToolScene>(L"ToolScene");

		//SceneManager::LoadScene(L"ToolScene");
		SceneManager::LoadScene(L"PlayScene");
	}
}
