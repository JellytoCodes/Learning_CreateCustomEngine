#pragma once
#include "KGraphicDevice_DX11.h"

#include "KResource.h"

namespace KEngine
{
	class Shader : public Resource
	{
		using Super = Resource;
	public :
		Shader();
		virtual ~Shader();

		HRESULT Load(const std::wstring& path) override;

		/*
		[Init: Vertex Shader(VS) 컴파일 + 생성]
		목적:
		- HLSL 파일을 컴파일해서 VS 바이트코드(Blob)를 만들고,
		  그 바이트코드로 ID3D11VertexShader 객체를 생성한다.

		왜 Blob(vsBlob)을 저장하나:
		- InputLayout 생성 시 VS의 입력 시그니처(semantic/format)를 기준으로
		  앱이 지정한 InputElementDesc가 호환되는지 검증해야 한다.
		- 그래서 CreateInputLayout에서 vsBlob가 필수로 사용된다.

		compile 설정:
		- vs_5_0 : Shader Model 5.0 Vertex Shader
		- DEBUG/SKIP_OPTIMIZATION: 디버깅 편의(성능 희생)
		*/
		void CreateVertexShader(const std::wstring& fileName);

		/*
		[Init: Pixel Shader(PS) 컴파일 + 생성]
		목적:
		- HLSL 파일을 컴파일해서 PS 바이트코드(Blob)를 만들고,
		  그 바이트코드로 ID3D11PixelShader 객체를 생성한다.

		PS 역할:
		- 래스터라이즈된 픽셀(프래그먼트)마다 최종 색/출력 값을 계산한다.
		- 결과는 OM 단계에서 RTV에 기록된다.

		compile 설정:
		- ps_5_0 : Shader Model 5.0 Pixel Shader
		*/
		void CreatePixelShader(const std::wstring& fileName);

		ID3D11VertexShader*		GetVertexShader() const { return mVS.Get(); }
		ID3DBlob*				GetVSBlob() const { return mVSBlob.Get(); }

		ID3D11PixelShader*		GetPixelShader() const { return mPS.Get(); }

	private :
		Microsoft::WRL::ComPtr<ID3DBlob>				mVSBlob;
		Microsoft::WRL::ComPtr<ID3D11VertexShader>		mVS;

		Microsoft::WRL::ComPtr<ID3DBlob>				mHSBlob;
		Microsoft::WRL::ComPtr<ID3D11HullShader>		mHS;

		Microsoft::WRL::ComPtr<ID3DBlob>				mDSBlob;
		Microsoft::WRL::ComPtr<ID3D11DomainShader>		mDS;

		Microsoft::WRL::ComPtr<ID3DBlob>				mGSBlob;
		Microsoft::WRL::ComPtr<ID3D11GeometryShader>	mGS;

		Microsoft::WRL::ComPtr<ID3DBlob>				mPSBlob;
		Microsoft::WRL::ComPtr<ID3D11PixelShader>		mPS;
	};	
}

