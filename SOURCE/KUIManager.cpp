#include "KUIManager.h"

namespace KEngine
{
	std::unordered_map<eUIType, std::unique_ptr<UIBase>>	UIManager::mUIs = {};
	std::stack<UIBase*>										UIManager::mUIBases = {};
	std::queue<eUIType>										UIManager::mRequestUIQueue = {};
	UIBase*													UIManager::mActiveUI = nullptr;

	void UIManager::Initialize()
	{

	}

	void UIManager::Update()
	{
		std::stack<UIBase*> uiBases = mUIBases;
		while (!uiBases.empty())
		{
			if (UIBase* uiBase = uiBases.top())
			{
				uiBase->Update();
				uiBases.pop();
			}
		}

		if (mRequestUIQueue.size() > 0)
		{
			eUIType requestUIType = mRequestUIQueue.front();
			mRequestUIQueue.pop();
			OnLoad(requestUIType);
		}
	}

	void UIManager::LateUpdate()
	{
		std::stack<UIBase*> uiBases = mUIBases;
		while (!uiBases.empty())
		{
			if (UIBase* uiBase = uiBases.top())
			{
				uiBase->LateUpdate();
				uiBases.pop();
			}
		}
	}

	void UIManager::Render(HDC hdc)
	{
		std::stack<UIBase*> uiBases = mUIBases;
		while (!uiBases.empty())
		{
			if (UIBase* uiBase = uiBases.top())
			{
				uiBase->Render(hdc);
				uiBases.pop();
			}
		}
	}

	void UIManager::OnLoad(eUIType type)
	{
		auto iter = mUIs.find(type);

		if (iter == mUIs.end())
		{
			OnFail();
			return;
		}
		OnComplete(iter->second.get());
	}

	void UIManager::OnComplete(UIBase* addUI)
	{
		if (addUI == nullptr)	return;

		addUI->Initialize();
		addUI->Active();
		addUI->Update();

		// 만약 현재 추가된 UI가 전체화면이라면
		// 전체화면인 UI 외 전부 비활성화

		if (addUI->IsFullScreen())
		{
			std::stack<UIBase*> uiBases = mUIBases;
			while (!uiBases.empty())
			{
				UIBase* uiBase = uiBases.top();
				uiBases.pop();
				if (uiBase)
				{
					uiBase->InActive();
				}
			}
		}

		mUIBases.push(addUI);
		mActiveUI = nullptr;
	}

	void UIManager::OnFail()
	{
		mActiveUI = nullptr;
	}

	void UIManager::Push(eUIType type)
	{
		mRequestUIQueue.push(type);
	}

	void UIManager::Pop(eUIType type)
	{
		if (mUIBases.size() <= 0)	return;

		UIBase* uibase = nullptr;
		while (mUIBases.size() > 0)
		{
			uibase = mUIBases.top();
			mUIBases.pop();


		}
	}
}
