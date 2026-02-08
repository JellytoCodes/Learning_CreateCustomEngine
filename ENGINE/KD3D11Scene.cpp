#include "KD3D11Scene.h"

#include "KResources.h"
#include "KSceneManager.h"

namespace KEngine
{
	D3D11Scene::D3D11Scene()
		: mbLoadCompleted(false)
	{

	}

	D3D11Scene::~D3D11Scene()
	{
		if (mResourcesLoad)
	    {
	        if (mResourcesLoad->joinable())
	            mResourcesLoad->join();
	            
	        delete mResourcesLoad;
	        mResourcesLoad = nullptr;
	    }
	}

	void D3D11Scene::Initialize()
	{
		mResourcesLoad = new std::thread(&D3D11Scene::resourcesLoad, this, std::ref(mMutex));
	}

	void D3D11Scene::Update()
	{
		if (mbLoadCompleted.load()) // 원자적 읽기
	    {
	        if (mResourcesLoad && mResourcesLoad->joinable())
	        {
				//만약 메인쓰레드가 종료되는데 자식쓰레드가 남아있다면
				//자식쓰레드를 메인쓰레드에 편입시켜 메인쓰레드가 종료되기전까지 block
	            mResourcesLoad->join();
	            delete mResourcesLoad;
	            mResourcesLoad = nullptr; // 중복 join 방지

				//메인쓰레드와 완전 분리 시켜 독립적인 쓰레드 운영가능
				//mResourcesLoad->detach();

	            SceneManager::LoadScene(L"PlayScene");
	        }
	    }
	}

	void D3D11Scene::LateUpdate()
	{
		Scene::LateUpdate();
	}

	void D3D11Scene::Render()
	{
		Scene::Render();
	}

	void D3D11Scene::OnEnter()
	{
		Scene::OnEnter();
	}

	void D3D11Scene::OnExit()
	{
		Scene::OnExit();
	}

	void D3D11Scene::resourcesLoad(std::mutex& m)
	{
		m.lock();
		{
			Resources::Load<Texture>(L"Cat", L"..\\Resources\\ChickenAlpha.bmp");
			Resources::Load<Texture>(L"Player", L"..\\Resources\\Player.bmp");
			Resources::Load<Texture>(L"SpringFloor", L"..\\Resources\\SpringFloor.bmp");
			Resources::Load<Texture>(L"HPBAR", L"..\\Resources\\HPBAR.bmp");
			Resources::Load<Texture>(L"PixelMap", L"..\\Resources\\pixelMap.bmp");
		}
		m.unlock();

		// complete
		mbLoadCompleted = true;
	}
}
