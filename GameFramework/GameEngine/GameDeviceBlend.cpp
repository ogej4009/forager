#include "GameDevice.h"
#include "GameBlend.h"

void GameDevice::BlendInit()
{
	// SrcColor : 이미지에 출력하려는 색깔
	// DestColor : 이 범위에 있는 기존컬러
	// +, * 할건지 설정 가능
	// (SrcColor*ScrFactor) + (DestColor*DestFactor) = 최종 컬러

	// *D3D11_BLEND_OP
	//D3D11_BLEND_OP_ADD;			C = srcC*srcF + dstC*dstF
	//D3D11_BLEND_OP_REV_SUBTRACT;	C = srcC*srcF - dstC*dstF
	//D3D11_BLEND_OP_SUBTRACT;		C = dstC*dstF - srcC*srcF  
	//D3D11_BLEND_OP_MAX;			C = max(srcC, dstC)
	//D3D11_BLEND_OP_MIN;			C = min(srcC, dstC)

	// * D3D11_BLEND
	// srcC=(rs,gs,bs), srcA=as 픽셀 셰이더가 출력한 RGBA 값들
	// dstC=(rd,gd,bd), dstA=ad 렌더 대상에 이미 저장되어 있는 RGBA 값들
	// f : srcf, dstf -> F : srcF, dstF 최종 알파성분

	//D3D11_BLEND_ZERO;				f = 0,0,0		F = 0
	//D3D11_BLEND_ONE;				f = 1,1,1		F = 1
	//D3D11_BLEND_SRC_COLOR;		f = rs,gs,bs
	//D3D11_BLEND_INV_SRC_COLOR;	f = 1-rs,1-gs,1-bs
	//D3D11_BLEND_SRC_ALPHA;		f = as,as,as	F = as
	//D3D11_BLEND_INV_SRC_ALPHA;	f = 1-as,1-as,1-as	F = 1-as
	//D3D11_BLEND_DEST_ALPHA;		f = ad,ad,ad	F = ad
	//D3D11_BLEND_INV_DEST_ALPHA;	f = 1-ad,1-ad,1-ad	F = 1-ad
	//D3D11_BLEND_DEST_COLOR;		f = rd,gd,bd
	//D3D11_BLEND_INV_DEST_COLOR;	f = 1-rd, 1-gd, 1-bd
	//D3D11_BLEND_SRC_ALPHA_SAT;	
	//D3D11_BLEND_BLEND_FACTOR;

	{
		D3D11_BLEND_DESC NewDesc;

		// 깊이버퍼가 쓰일때 알파값으로 영향을 줄것이냐 아닐것이냐를 결정한다. 
		NewDesc.AlphaToCoverageEnable = false;
		NewDesc.IndependentBlendEnable = false;
		NewDesc.RenderTarget[0];
		memset(&NewDesc.RenderTarget[0], 0, sizeof(NewDesc.RenderTarget[0]));

		NewDesc.RenderTarget[0].BlendEnable = TRUE;
		NewDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		NewDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;

		NewDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		NewDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;

		NewDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		NewDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		NewDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;


		GameBlend::Create(L"DEF_BLEND", NewDesc);
	}

	{
		D3D11_BLEND_DESC NewDesc;

		NewDesc.AlphaToCoverageEnable = false;
		NewDesc.IndependentBlendEnable = false;
		NewDesc.RenderTarget[0];
		memset(&NewDesc.RenderTarget[0], 0, sizeof(NewDesc.RenderTarget[0]));

		NewDesc.RenderTarget[0].BlendEnable = TRUE; // 혼합 활성화 TRUE, 비활성화 FALSE
		NewDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		NewDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD; // 혼합 연산자
		NewDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA; // srcf
		NewDesc.RenderTarget[0].DestBlend = D3D11_BLEND_DEST_ALPHA;  // dstf

		NewDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD; // 혼합 연산자 
		NewDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;  // srcF
		NewDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;  // dstF


		GameBlend::Create(L"TEST", NewDesc);
	}
}