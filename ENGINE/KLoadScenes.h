#pragma once

#include "KD3D11Scene.h"
#include "../SOURCE/KSceneManager.h"

#include "KPlayScene.h"
#include "KTitleScene.h"
#include "KToolScene.h"

namespace KEngine
{
	void LoadScenes()
	{
		//SceneManager::CreateScene<TitleScene>(L"TitleScene");
		//SceneManager::CreateScene<PlayScene>(L"PlayScene");
		//SceneManager::CreateScene<ToolScene>(L"ToolScene");
		SceneManager::CreateScene<D3D11Scene>(L"D3D11Scene");

		//SceneManager::LoadScene(L"ToolScene");
		//SceneManager::LoadScene(L"PlayScene");
		SceneManager::LoadScene(L"D3D11Scene");
	}
}
