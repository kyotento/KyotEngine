#include "stdafx.h"
#include "GaussianBlur.h"
#include "PostEffect.h"

GaussianBlur::GaussianBlur()
{
}


GaussianBlur::~GaussianBlur()
{
}

//初期化。
void GaussianBlur::Init(ID3D11ShaderResourceView* srcTextureSRV, float blurPow)
{
	//ソーステクスチャのSRVをコピー。
	m_srcTextureSRV = srcTextureSRV;
	//ブラーの強さを保持。
	m_blurPower = blurPow;

	//テクスチャの情報を取得。
	ID3D11Texture2D* texture;
	//SRVのテクスチャを取得する。
	srcTextureSRV->GetResource((ID3D11Resource**)&texture);

	//テクスチャ情報の取得。
	D3D11_TEXTURE2D_DESC textureDesc;
	texture->GetDesc(&textureDesc);
	//テクスチャの情報を取得後、参照カウンタを下す。
	texture->Release();

	m_srcTextureWidth = textureDesc.Width;			//テクスチャの幅を保持。
	m_srcTextureHeight = textureDesc.Height;		//テクスチャの高さを保持。

	/// <remarks>
	/// X軸とY軸を分けて処理したほうがテクスチャがきれいにできる(らしい)。
	/// </remarks>	
	//Xブラー用のレンダリングターゲットを作成。(横の解像度を半分にする)。
	m_renderTarget[enRenderTarget_X].Create(textureDesc.Width / 2, textureDesc.Height, textureDesc.Format);
	//Yブラー用のレンダリングターゲットを作成。(縦横の解像度を半分にする)。
	m_renderTarget[enRenderTarget_Y].Create(textureDesc.Width / 2, textureDesc.Height / 2, textureDesc.Format);

	//シェーダーをロード。
	m_vsXBlur.Load("Assets/shader/GaussianBlur.fx", "VSXBlur", Shader::EnType::VS);
	m_vsYBlur.Load("Assets/shader/GaussianBlur.fx", "VSYBlur", Shader::EnType::VS);
	m_psBlur.Load("Assets/shader/GaussianBlur.fx", "PSBlur", Shader::EnType::PS);

	//VRAM上に定数バッファを作成。(領域確保のため)。
	m_blurCbGpu.Create(nullptr, sizeof(SBlurParam));

	//初期化したのでフラグを返す。
	m_isInit = true;
}

//ブラーの重みを更新。
void GaussianBlur::UpdateWeights()
{
	//重みのトータル。
	float total = 0;
	//ガウスフィルタの重みを更新。
	for (int i = 0; i < NUM_WEIGHTS; i++) {
		m_blurParam.weights[i] = expf(-0.5f*(float)(i*i) / m_blurPower);
		total += 2.0f*m_blurParam.weights[i];
	}

	// 規格化。重みのトータルが1.0になるように、全体の重みで除算。
	for (int i = 0; i < NUM_WEIGHTS; i++) {
		m_blurParam.weights[i] /= total;
	}
}

void GaussianBlur::Execute(PostEffect& postEffect)
{
	//初期化がされていないとき、処理を行わない。
	if (!m_isInit) {
		return;
	}

	auto deviceContext = g_graphicsEngine->GetD3DDeviceContext();

	//ブラーの重みを更新。
	UpdateWeights();

	//重みの更新後、VRAM上の定数バッファも更新。
	//メインメモリの内藤をVRAMにコピー。
	auto d3d11CbGPU = m_blurCbGpu.GetD3D11Buffer();
	deviceContext->UpdateSubresource(d3d11CbGPU, 0, nullptr, &m_blurParam, 0, 0);
	//レジスタb0にm_blurCbGPUのアドレスと設定する。
	deviceContext->PSSetConstantBuffers(0, 1, &d3d11CbGPU);


	//Xブラー用のレンダリングターゲットに変更する。
	g_graphicsEngine->ChangeRenderTarget(
		&m_renderTarget[enRenderTarget_X],
		m_renderTarget[enRenderTarget_X].GetViewport()
	);
	//ソーステクスチャのアドレスをt0レジスタに設定する。
	deviceContext->VSSetShaderResources(0, 1, &m_srcTextureSRV);
	deviceContext->PSSetShaderResources(0, 1, &m_srcTextureSRV);

	//フルスクリーン描画を行ってブラーを実行。
	postEffect.DrawFullScreenQuadPrimitive(deviceContext, m_vsXBlur, m_psBlur);


	//Yブラー用のレンダリングターゲットに変更する。
	g_graphicsEngine->ChangeRenderTarget(
		&m_renderTarget[enRenderTarget_Y],
		m_renderTarget[enRenderTarget_Y].GetViewport()
	);
	//Yブラーをかけるソーステクスチャのアドレスをt0に設定する。
	//YブラーをかけるのはXブラーをかけたテクスチャになる。
	auto srcTextureSrv = m_renderTarget[enRenderTarget_X].GetRenderTargetSRV();
	deviceContext->VSSetShaderResources(0, 1, &srcTextureSrv);
	deviceContext->PSSetShaderResources(0, 1, &srcTextureSrv);

	//フルスクリーン描画を行ってブラーを実行。
	postEffect.DrawFullScreenQuadPrimitive(
		deviceContext, m_vsYBlur, m_psBlur
	);

}