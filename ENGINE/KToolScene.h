#pragma once
#include "KTile.h"
#include "../SOURCE/KScene.h"

namespace KEngine
{
	class Player;

	class ToolScene : public Scene
	{
	public :
		ToolScene();
		~ToolScene();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;

		void OnEnter() override;
		void OnExit() override;

		void Save();
		void Load();

	private:
		std::vector<Tile*> mTiles;
	};	
}

LRESULT CALLBACK WndTileProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);