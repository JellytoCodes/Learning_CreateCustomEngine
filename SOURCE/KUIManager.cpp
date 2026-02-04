#include "KUIManager.h"
#include "KUIButton.h"
#include "KUIHUD.h"

namespace KEngine
{
	std::unordered_map<eUIType, std::unique_ptr<UIBase>>	UIManager::mUIs = {};
	std::stack<UIBase*>										UIManager::mUIBases = {};
	std::queue<eUIType>										UIManager::mRequestUIQueue = {};
	UIBase*													UIManager::mActiveUI = nullptr;

	void UIManager::Initialize()
	{
		std::unique_ptr<UIHUD> hud = std::make_unique<UIHUD>();
		mUIs.insert(std::make_pair(eUIType::HpBar, std::move(hud)));

		std::unique_ptr<UIButton> button = std::make_unique<UIButton>();
		mUIs.insert(std::make_pair(eUIType::Button, std::move(button)));
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

	void UIManager::Release()
	{
		mUIs.clear();
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

		std::stack<UIBase*> tempStack;

		UIBase* uiBase = nullptr;
		while (mUIBases.size() > 0)
		{
			uiBase = mUIBases.top();
			mUIBases.pop();

			if (uiBase->GetUIType() != type)
			{
				tempStack.push(uiBase);
				continue;
			}

			if (uiBase->IsFullScreen())
			{
				std::stack<UIBase*> uiBases = mUIBases;
				while (!uiBases.empty())
				{
					UIBase* uiBase = uiBases.top();
					uiBases.pop();
					if (uiBase)
					{
						uiBase->Active();
						break;
					}
				}
			}

			uiBase->UIClear();
		}

		while (tempStack.size() > 0)
		{
			uiBase = tempStack.top();
			tempStack.pop();
			mUIBases.push(uiBase);
		}
	}
}
