#include "stdafx.h"
#include "Bloom.h"
#include "PostEffect.h"

Bloom::Bloom()
{
}


Bloom::~Bloom()
{
}

void Bloom::InitRenderTarget()
{
	//輝度抽出用のレンダリングターゲットを作成する。
	m_luminanceRT.Create(
		FRAME_BUFFER_W,
		FRAME_BUFFER_H,
		DXGI_FORMAT_R16G16B16A16_FLOAT
	);
}

//描画処理。
void Bloom::Draw(PostEffect& postEffect)
{
	//デバイスコンテキストの初期化。
	auto deviceContext = g_graphicsEngine->GetD3DDeviceContext();
	deviceContext->PSSetSamplers(0, 1, &m_samplerState);

	//αブレンドを無効にする。
	float blendFactor[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	deviceContext->OMSetBlendState(m_disableBlendState, blendFactor, 0xffffffff);

	//輝度抽出用のレンダリングターゲットに変更。
	g_graphicsEngine->ChangeRenderTarget(&m_luminanceRT, m_luminanceRT.GetViewport());

	//レンダリングターゲットのクリア。
	float clearColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	m_luminanceRT.ClearRenderTarget(clearColor);

	//シーンをテクスチャとする。
	auto mainRTTexSRV = IGameObjectManager().GetMainRenderTarget()->GetRenderTargetSRV();
	deviceContext->PSSetShaderResources(0, 1, &mainRTTexSRV);

	//フルスクリーン描画。
	postEffect.DrawFullScreenQuadPrimitive(deviceContext, m_vs, m_psLuminance);
}