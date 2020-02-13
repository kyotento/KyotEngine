/// <summary>
/// ガウシアンブラー。
/// </summary>
#pragma once
#include "ConstantBufferGPU.h"
#include "RenderTarget.h"

class PostEffect;
class GaussianBlur
{
public:
	GaussianBlur();
	~GaussianBlur();

	/// <summary>
	/// 初期化。
	/// </summary>
	/// <param name="srtTextureSRV">テクスチャ(ブラーをかける)のSRV</param>
	/// <param name="blurPow">ブラーの強さ</param>
	void Init(ID3D11ShaderResourceView* srtTextureSRV, float blurPow);

	/// <summary>
	/// ブラーの重み更新。
	/// </summary>
	void UpdateWeights();

	/// <summary>
	/// ブラーの実行。
	/// </summary>
	/// <param name="postEffect">
	/// ポストエフェクトのインスタンス。
	/// 全画面描画の機能を使う。
	/// </param>
	/// <remarks>
	/// Init関数を呼び出した後で実行するように。
	/// </remarks>
	void Execute(PostEffect& postEffect);

	/// <summary>
	/// ブラーをかけた結果のテクスチャSRVを取得。
	/// </summary>
	/// <returns></returns>
	ID3D11ShaderResourceView* GetResultTextureSRV()
	{
		return m_renderTarget[enRenderTarget_Y].GetRenderTargetSRV();
	}
private:

	/// <summary>
	/// レンダリングターゲット。
	/// </summary>
	enum EnRenderTarget {
		enRenderTarget_X,		//Xブラーの書き込み先となるレンダリングターゲット。
		enRenderTarget_Y,		//Yブラーの書き込み先となるレンダリングターゲット。
		enRenderTargetNum		//レンダリングターゲットの数。
	};

	static const int NUM_WEIGHTS = 8;	//カウスフィルタの重みの数。
	/// <summary>
	/// ブラー用のパラメータバッファ。
	/// </summary>
	/// <remarks>
	/// これを変更したら、Assets/shader/GaussianBlur.fxのCBBlurの中身も変更する。
	/// </remarks>
	struct SBlurParam {
		float weights[NUM_WEIGHTS];
	};

	unsigned int m_srcTextureWidth = 0;						//ソーステクスチャの幅。
	unsigned int m_srcTextureHeight = 0;					//ソーステクスチャの高さ。

	float m_blurPower = 25.0f;								//ブラーの強さ。

	bool m_isInit = false;									//初期化したか否か。

	RenderTarget m_renderTarget[enRenderTargetNum];			//レンダリングターゲット。

	ID3D11ShaderResourceView* m_srcTextureSRV = nullptr;	//ソーステクスチャのSRV

	Shader m_vsXBlur;							//Xブラー用の頂点シェーダー。
	Shader m_vsYBlur;							//Yブラー用の頂点シェーダー。
	Shader m_psBlur;							//ブラー用のピクセルシェーダー。

	SBlurParam m_blurParam;						//ブラー用のパラメータ。
	ConstantBufferGPU m_blurCbGpu;				//ブラー用の定数バッファ(GPU側)

};

