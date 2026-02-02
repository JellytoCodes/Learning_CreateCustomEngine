#include "KToolScene.h"

#include "KCamera.h"
#include "KObject.h"
#include "KRenderer.h"
#include "KResources.h"
#include "KTile.h"
#include "KTileMapRenderer.h"

namespace KEngine
{
	ToolScene::ToolScene()
	{

	}

	ToolScene::~ToolScene()
	{

	}

	void ToolScene::Initialize()
	{
		// Main Camera
		GameObject* camera = KObject::Instantiate<GameObject>(KEngine::eLayerType::None, KMath::Vector2(512.f, 256.f));
		Camera* cameraComp = camera->AddComponent<Camera>();
		KRenderer::mainCamera = cameraComp;

		// Tile
		{
			Tile* tile = KObject::Instantiate<Tile>(eLayerType::Tile);
			TileMapRenderer* tmr = tile->AddComponent<TileMapRenderer>();
			Texture* texture = Resources::Find<Texture>(L"SpringFloor");
			tmr->SetTexture(texture);	
		}

		Scene::Initialize();
	}

	void ToolScene::Update()
	{
		Scene::Update();
	}

	void ToolScene::LateUpdate()
	{
		Scene::LateUpdate();
	}

	void ToolScene::Render(HDC hdc)
	{
		Scene::Render(hdc);

		for (size_t i = 1 ; i < 25 ; i++)
		{
			MoveToEx(hdc, (16 * 3) * i, 0, NULL);
			LineTo(hdc, (16 * 3 )*i, 1000);
		}

		for (size_t i = 1 ; i < 25 ; i++)
		{
			MoveToEx(hdc, 0, (16 * 3) * i, NULL);
			LineTo(hdc, 1000, (16 * 3) * i);
		}
	}

	void ToolScene::OnEnter()
	{
		Scene::OnEnter();
	}

	void ToolScene::OnExit()
	{
		Scene::OnExit();
	}
}
