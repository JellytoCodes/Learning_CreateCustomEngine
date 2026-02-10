#pragma once
#include "KResource.h"
#include "KShader.h"
#include "KTexture.h"

namespace KEngine
{
	class Material : public Resource
	{
	public :
		struct Data
		{
			std::wstring albedo; //diffuse
		};

		Material();
		virtual ~Material();

		virtual HRESULT Save(const std::wstring& path) override;
		virtual HRESULT Load(const std::wstring& path) override;

		void Bind();
		void BindShader();
		void BindTextures();

		void SetShader(KEngine::Shader* shader) { mShader = shader; }

	private:
		KGraphics::eRenderingMode	mMode;
		Data						mData;

		KEngine::Texture*			mAlbedoTexture;
		KEngine::Shader*			mShader;
	};
}

