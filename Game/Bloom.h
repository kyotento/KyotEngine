/// <summary>
/// ブルーム。
/// </summary>
#pragma once
#include "GaussianBlur.h"

class PostEffect;
class Bloom
{
public:
	Bloom();
	~Bloom();

	/// <summary>
	/// 初期化。
	/// </summary>
	void Init();

	/// <summary>
	/// 輝度抽出用レンダーターゲットの初期化。
	/// </summary>
	void InitRenderTarget();

	/// <summary>
	/// シェーダーの初期化。
	/// </summary>
	void InitShader();

	/// <summary>
	/// αブレンディングsyテートの初期化。
	/// </summary>
	void InitAlphaBlendState();

	/// <summary>
	/// サンプラーステートの初期化。
	/// </summary>
	void InitSamplerState();

	/// <summary>
	/// 描画処理。
	/// </summary>
	/// <param name="postEffect">ポストエフェクト</param>
	void Draw(PostEffect& postEffect);

private:

	static const int NUM_DOWN_SAMPLE = 4;				//ダウンサンプリングの回数。

	ID3D11SamplerState* m_samplerState = nullptr;		//サンプラステート。
	ID3D11BlendState* m_disableBlendState = nullptr;	//アルファブレンディングを無効にするブレンディングステート。
	ID3D11BlendState* m_finalBlendState = nullptr;		//最終合成用のブレンディングステート。

	Shader m_vs;						//何もしない頂点シェーダー。
	Shader m_psLuminance;				//輝度抽出用のピクセルシェーダー。
	Shader m_psCombine;					//ぼかし画像合成用のピクセルシェーダー。
	Shader m_psFinal;					//最終合成用のピクセルシェーダー。

	RenderTarget m_luminanceRT;			//輝度を抽出するレンダリングターゲット。
	RenderTarget m_blurCombineRT;		//ブラーの画像を合成するレンダリングターゲット。

	GaussianBlur m_gausianBlur[NUM_DOWN_SAMPLE];	//輝度をぼかすためのガウシアンブラー。
		
};

