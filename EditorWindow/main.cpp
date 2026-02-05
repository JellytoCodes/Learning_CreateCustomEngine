
#include "framework.h"
#include "EditorWindow.h"

#include "../SOURCE/KApplication.h"
#include "../ENGINE/KLoadScenes.h"
#include "../SOURCE/KCollisionManager.h"

#pragma comment (lib, "../Libraries/Lib/Engine/ENGINE.lib")

KEngine::Application application;

ULONG_PTR gpToken;
Gdiplus::GdiplusStartupInput gpsi;

#define MAX_LOADSTRING 100

HINSTANCE           hInst;                    
WCHAR               szTitle[MAX_LOADSTRING];
WCHAR               szWindowClass[MAX_LOADSTRING];

ATOM                MyRegisterClass(HINSTANCE hInstance, const wchar_t* name, WNDPROC proc);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR    lpCmdLine, _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    //_CrtSetBreakAlloc(341);

    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_EDITORWINDOW, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance, szWindowClass, WndProc);
    //MyRegisterClass(hInstance, L"TILEWINDOW", WndTileProc);

    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_EDITORWINDOW));

    MSG msg;

    // GetMessage()
    // 프로세스에서 발생한 메시지를 메세지 큐에서 가져오는 함수
    // 메세지큐에 아무것도 없다면 아무 메세지도 가져오지 않게된다.

    // PeekMessage : 메세지큐에 메세지 유무에 상관없이 함수가 리턴된다.
    //               리턴값이 true인 경우 메세지가 있고 false인 경우 메세지가 없다.
    while (true)
    {
	    if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	    {
		    if (msg.message == WM_QUIT) break;

            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
	    }
        else
        {
			application.Run();
        }
    }
    application.Release();

    Gdiplus::GdiplusShutdown(gpToken);

    return (int) msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance, const wchar_t* name, WNDPROC proc)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = proc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_EDITORWINDOW));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_EDITORWINDOW);
    wcex.lpszClassName  = name;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

    const LONG width = 1600;
    const LONG height = 900;

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, width, height, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)   return FALSE;

    application.CreateApplication(hWnd, width, height);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

    Gdiplus::GdiplusStartup(&gpToken, &gpsi, NULL);

	application.Initialize();

	// load Scenes
    //KEngine::LoadResources();
    KEngine::LoadScenes();

	int a = 0;
    srand((UINT)&a);

    KEngine::Scene* activeScene = KEngine::SceneManager::GetActiveScene();
    std::wstring name = activeScene->GetName();

	/*if (name == L"ToolScene")
	{
		HWND toolhWnd = CreateWindowW(L"TILEWINDOW", L"TileWindow", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, width, height, nullptr, nullptr, hInstance, nullptr);

		KEngine::Texture* texture = KEngine::Resources::Find<KEngine::Texture>(L"SpringFloor");

		RECT rect = {0, 0, (LONG)texture->GetWidth(), (LONG)texture->GetHeight()};

		UINT toolWidth = rect.right - rect.left;
		UINT toolHeight = rect.bottom - rect.top;

		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

		SetWindowPos(toolhWnd, nullptr, width, 0, toolWidth, toolHeight, 0);
		ShowWindow(toolhWnd, true);
	    UpdateWindow(toolhWnd);	
	}*/

	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;

    		// DC(Device Context)란 화면에 출력에 필요한 모든 정보(폰트, 선의 굵기, 색상 등을 어떻게 그려줄 것인지)를 
			// 가지는 데이터 구조체이며 GDI모듈에 의해 관리된다.
			// 화면 출력에 필요한 모든 경우는 WINAPI에서는 DC를 통해서 작업을 진행할 수 있다.
            HDC hdc = BeginPaint(hWnd, &ps);

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

INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
