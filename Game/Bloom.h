/// <summary>
/// ブルーム。
/// </summary>
#pragma once

class PostEffect;
class Bloom
{
public:
	Bloom();
	~Bloom();

	/// <summary>
	/// 輝度抽出用レンダーターゲットの初期化。
	/// </summary>
	void InitRenderTarget();

	/// <summary>
	/// 描画処理。
	/// </summary>
	/// <param name="postEffect">ポストエフェクト</param>
	void Draw(PostEffect& postEffect);

private:

	ID3D11SamplerState* m_samplerState = nullptr;		//サンプラステート。
	ID3D11BlendState* m_disableBlendState = nullptr;	//アルファブレンディングを無効にするブレンディングステート。

	Shader m_vs;						//何もしない頂点シェーダー。
	Shader m_psLuminance;				//輝度抽出用のピクセルシェーダー。

	RenderTarget m_luminanceRT;			//輝度を抽出するレンダリングターゲット。
		
};

