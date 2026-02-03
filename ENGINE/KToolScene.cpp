#include "KToolScene.h"

#include "KCamera.h"
#include "KObject.h"
#include "KRenderer.h"
#include "KResources.h"
#include "KTile.h"
#include "KTileMapRenderer.h"
#include "KInput.h"
#include "KCameraScript.h"

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
		camera->AddComponent<CameraScript>();
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

		if (Input::GetKeyDown(eKeyCode::LButton))
		{
			KMath::Vector2 pos = Input::GetMousePosition();
			pos = KRenderer::mainCamera->CalculateTilePosition(pos);

			if (pos.x < 0.f || pos.y < 0.f) return;

			int xIndex = pos.x / TileMapRenderer::TileSize.x;
			int yIndex = pos.y / TileMapRenderer::TileSize.y;

			Tile* tile = KObject::Instantiate<Tile>(eLayerType::Tile, KMath::Vector2(xIndex * TileMapRenderer::TileSize.x, yIndex * TileMapRenderer::TileSize.y));
			TileMapRenderer* tmr = tile->AddComponent<TileMapRenderer>();
			Texture* texture = Resources::Find<Texture>(L"SpringFloor");
			tmr->SetTexture(texture);
			tmr->SetIndex(TileMapRenderer::SelectedIndex);

			tile->SetIndexPosition(xIndex, yIndex);

			mTiles.push_back(tile);
		}

		if (Input::GetKeyDown(eKeyCode::S))
		{
			Save();
		}

		if (Input::GetKeyDown(eKeyCode::L))
		{
			Load();
		}
	}

	void ToolScene::Render(HDC hdc)
	{
		Scene::Render(hdc);

		for (size_t i = 1 ; i < 25 ; i++)
		{
			KMath::Vector2 pos
				= KRenderer::mainCamera->CalculatePosition(KMath::Vector2(TileMapRenderer::TileSize.x * i, 0.0f));

			MoveToEx(hdc, pos.x, 0, NULL);
			LineTo(hdc, pos.x, 1000);
		}

		for (size_t i = 1 ; i < 25 ; i++)
		{
			KMath::Vector2 pos
				= KRenderer::mainCamera->CalculatePosition(KMath::Vector2(0.0f, TileMapRenderer::TileSize.y * i));

			MoveToEx(hdc, 0, pos.y, NULL);
			LineTo(hdc, 1400, pos.y);
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

	void ToolScene::Save()
	{
		// open a file name
		OPENFILENAME ofn = {};

		wchar_t szFilePath[256] = {};

		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = NULL;
		ofn.lpstrFile = szFilePath;
		ofn.lpstrFile[0] = '\0';
		ofn.nMaxFile = 256;
		ofn.lpstrFilter = L"Tile\0*.tile\0";
		ofn.nFilterIndex = 1;
		ofn.lpstrFileTitle = NULL;
		ofn.nMaxFileTitle = 0;
		ofn.lpstrInitialDir = NULL;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

		if (false == GetSaveFileName(&ofn))	return;

		FILE* pFile = nullptr;
		_wfopen_s(&pFile, szFilePath, L"wb");

		for (Tile* tile : mTiles)
		{
			TileMapRenderer* tmr = tile->GetComponent<TileMapRenderer>();
			Transform* tr = tile->GetComponent<Transform>();

			KMath::Vector2 sourceIndex = tmr->GetIndex();
			KMath::Vector2 position = tr->GetPosition();

			int x = sourceIndex.x;
			fwrite(&x, sizeof(int), 1, pFile);
			int y = sourceIndex.y;
			fwrite(&y, sizeof(int), 1, pFile);

			x = position.x;
			fwrite(&x, sizeof(int), 1, pFile);
			y = position.y;
			fwrite(&y, sizeof(int), 1, pFile);
		}
		
		fclose(pFile);
	}

	void ToolScene::Load()
	{
		OPENFILENAME ofn = {};

		wchar_t szFilePath[256] = {};

		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = NULL;
		ofn.lpstrFile = szFilePath;
		ofn.lpstrFile[0] = '\0';
		ofn.nMaxFile = 256;
		ofn.lpstrFilter = L"All\0*.*\0Text\0*.TXT\0";
		ofn.nFilterIndex = 1;
		ofn.lpstrFileTitle = NULL;
		ofn.nMaxFileTitle = 0;
		ofn.lpstrInitialDir = NULL;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

		if (false == GetOpenFileName(&ofn))	return;

		FILE* pFile = nullptr;
		_wfopen_s(&pFile, szFilePath, L"rb");

		while (true)
		{
			int idxX = 0;
			int idxY = 0;

			int posX = 0;
			int posY = 0;

			if (fread(&idxX, sizeof(int), 1, pFile) == NULL)	break;
			if (fread(&idxY, sizeof(int), 1, pFile) == NULL)	break;
			if (fread(&posX, sizeof(int), 1, pFile) == NULL)	break;
			if (fread(&posY, sizeof(int), 1, pFile) == NULL)	break;

			Tile* tile = KObject::Instantiate<Tile>(eLayerType::Tile, KMath::Vector2(posX, posY));
			TileMapRenderer* tmr = tile->AddComponent<TileMapRenderer>();
			tmr->SetTexture(Resources::Find<Texture>(L"SpringFloor"));
			tmr->SetIndex(KMath::Vector2(idxX, idxY));

			mTiles.push_back(tile);
		}

		fclose(pFile);
	}
}

LRESULT CALLBACK WndTileProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_LBUTTONDOWN:
        {
			POINT mousePos = { };
			GetCursorPos(&mousePos);
			ScreenToClient(hWnd, &mousePos);

			KMath::Vector2 mousePosition;
			mousePosition.x = mousePos.x;
			mousePosition.y = mousePos.y;

			int idxX = mousePosition.x / KEngine::TileMapRenderer::OriginTileSize.x;
			int idxY = mousePosition.y / KEngine::TileMapRenderer::OriginTileSize.y;

			KEngine::TileMapRenderer::SelectedIndex = KMath::Vector2(idxX, idxY);
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);

    		KEngine::Texture* texture = KEngine::Resources::Find<KEngine::Texture>(L"SpringFloor");

    		TransparentBlt(hdc
    			, 0, 0
				, texture->GetWidth()
				, texture->GetHeight()
				, texture->GetHdc()
				, 0, 0
				, texture->GetWidth()
				, texture->GetHeight()
				, RGB(255, 0, 255));

            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}