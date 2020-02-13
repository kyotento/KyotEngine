#include "stdafx.h"
#include "Bloom.h"
#include "PostEffect.h"

Bloom::Bloom()
{

}


Bloom::~Bloom()
{
	if (m_disableBlendState != nullptr) {
		m_disableBlendState->Release();
	}

	if (m_samplerState != nullptr) {
		m_samplerState->Release();
	}
	if (m_finalBlendState != nullptr) {
		m_finalBlendState->Release();
	}
}

void Bloom::Init()
{
	//レンダーターゲットの初期化。
	InitRenderTarget();

	//シェーダーの初期化。
	InitShader();

	//αブレンディングステートの初期化。
	InitAlphaBlendState();

	//サンプラーステートの初期化。
	InitSamplerState();

	//ガウシアンブラーの初期化。
	ID3D11ShaderResourceView* srcBlirTexture = m_luminanceRT.GetRenderTargetSRV();
	for (auto& gaussianBlur : m_gausianBlur) {
		gaussianBlur.Init(srcBlirTexture, 25.f);
		//次のガウシアンブラーで使用するソーステクスチャを設定する。
		srcBlirTexture = gaussianBlur.GetResultTextureSRV();
	}
}

//レンダリングターゲットの初期化。
void Bloom::InitRenderTarget()
{
	//輝度抽出用のレンダリングターゲットを作成する。
	m_luminanceRT.Create(
		FRAME_BUFFER_W,
		FRAME_BUFFER_H,
		DXGI_FORMAT_R16G16B16A16_FLOAT
	);

	//フレームバッファの1/2の解像度のボケ画像合成用のレンダリングターゲットを作成する。
	//一番解像度が高いものが1/2のためこの解像度。
	m_blurCombineRT.Create(
		FRAME_BUFFER_W / 2,
		FRAME_BUFFER_H / 2,
		DXGI_FORMAT_R16G16B16A16_FLOAT
	);
}

//シェーダーの初期化。
void Bloom::InitShader()
{
	m_vs.Load("Assets/shader/bloom.fx", "VSMain", Shader::EnType::VS);
	m_psLuminance.Load("Assets/shader/bloom.fx", "PSSamplingLuminance", Shader::EnType::PS);
	m_psFinal.Load("Assets/shader/bloom.fx", "PSFinal", Shader::EnType::PS);

	//ボケ画像合成用のピクセルシェーダーをロードする。
	m_psCombine.Load("Assets/shader/bloom.fx", "PSCombine", Shader::EnType::PS);
}

//αブレンディングステートの初期化。
void Bloom::InitAlphaBlendState()
{
	CD3D11_DEFAULT defaultSettings;
	//デフォルトセッティングで初期化する。
	CD3D11_BLEND_DESC blendDesc(defaultSettings);
	auto device = g_graphicsEngine->GetD3DDevice();

	//ブレンドステートの作成。
	device->CreateBlendState(&blendDesc, &m_disableBlendState);

	//最終合成用のブレンドステートを作成する。
	//最終合成は加算合成。
	blendDesc.RenderTarget[0].BlendEnable = true;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	device->CreateBlendState(&blendDesc, &m_finalBlendState);
}

//サンプラーステートの初期化。
void Bloom::InitSamplerState()
{
	D3D11_SAMPLER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	g_graphicsEngine->GetD3DDevice()->CreateSamplerState(&desc, &m_samplerState);
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

	//レンダリングターゲットのクリア。
	float clearColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	m_luminanceRT.ClearRenderTarget(clearColor);

	//輝度抽出用のレンダリングターゲットに変更。
	g_graphicsEngine->ChangeRenderTarget(&m_luminanceRT, m_luminanceRT.GetViewport());


	//シーンをテクスチャとする。
	auto mainRTTexSRV = IGameObjectManager().GetMainRenderTarget()->GetRenderTargetSRV();
	deviceContext->PSSetShaderResources(0, 1, &mainRTTexSRV);

	//フルスクリーン描画。
	postEffect.DrawFullScreenQuadPrimitive(deviceContext, m_vs, m_psLuminance);

	//輝度テクスチャをガウシアンブラーでぼかす。
	for (auto& GaussianBlur : m_gausianBlur) {
		GaussianBlur.Execute(postEffect);
	}

	///<remarks>
	/// ガウシアンブラーでぼかした画像を1/2の解像度のレンダリングターゲットに使用して合成する。
	/// </remarks>
	//レンダリングターゲットをぼかし画像合成用のモノにする。
	g_graphicsEngine->ChangeRenderTarget(&m_blurCombineRT, m_blurCombineRT.GetViewport());
	//ガウシアンブラーをかけたテクスチャをt0～t3レジスタに設定する。
	for (int registerNo = 0; registerNo < NUM_DOWN_SAMPLE; registerNo++) {
		auto srv = m_gausianBlur[registerNo].GetResultTextureSRV();
		deviceContext->PSSetShaderResources(registerNo, 1, &srv);
	}

	//フルスクリーン描画。
	postEffect.DrawFullScreenQuadPrimitive(deviceContext, m_vs, m_psCombine);

	/// <remarks>
	/// ぼかした絵を加算合成でメインレンダリングターゲットに合成。
	/// </remarks>
	auto mainRT = IGameObjectManager().GetMainRenderTarget();
	g_graphicsEngine->ChangeRenderTarget(mainRT, mainRT->GetViewport());

	//合成したボケテクスチャのアドレスをt0レジスタに設定する。
	auto srv = m_blurCombineRT.GetRenderTargetSRV();
	deviceContext->PSSetShaderResources(0, 1, &srv);

	//加算合成用のブレンディングステートを設定する。
	deviceContext->OMSetBlendState(m_finalBlendState, blendFactor, 0xffffffff);
	//フルスクリーン描画。
	postEffect.DrawFullScreenQuadPrimitive(deviceContext, m_vs, m_psFinal);

	//ブレンディングステートを戻す。
	deviceContext->OMSetBlendState(m_disableBlendState, blendFactor, 0xffffffff);
}