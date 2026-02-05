#pragma once

#include "KD3D11Scene.h"
#include "../SOURCE/KSceneManager.h"

namespace KEngine
{
	void LoadScenes()
	{
		SceneManager::CreateScene<D3D11Scene>(L"D3D11Scene");

		SceneManager::LoadScene(L"D3D11Scene");
	}
}
