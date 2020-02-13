#pragma once

/*!
 *@brief	グラフィックスエンジン。
 */
#include "../PostEffect.h"

enum EnRenderMode
{
	enRenderMode_Invalid,			//不正レンダリングモード。
	enRenderMode_CreateShadowMap,   //シャドウマップ生成。
	enRenderMode_Normal,			//通常レンダリングモード。
	enRenderMode_Num,				//レンダリングモードの数。
};


class RenderTarget;
class GraphicsEngine
{
public:
	GraphicsEngine();
	~GraphicsEngine();
	/*!
	 *@brief	初期化。
	 *@param[in]	hWnd		ウィンドウハンドル。
	 */
	void Init(HWND hWnd);
	/*!
	 *@brief	解放。
	 */
	void Release();
	/*!
	 *@brief	D3D11デバイスを取得。
	 */
	ID3D11Device* GetD3DDevice()
	{
		return m_pd3dDevice;
	}
	/*!
	 *@brief	D3D11デバイスコンテキストを取得。
	 */
	ID3D11DeviceContext* GetD3DDeviceContext()
	{
		return m_pd3dDeviceContext;
	}
	/*!
	 *@brief	描画開始。
	 */
	void BegineRender();
	/*!
	 *@brief	描画終了。
	 */

	void EndRender();

	/// <summary>
		/// SpriteBatchの取得
		/// </summary>
		/// <remarks>
		/// エンジン内部で使用されます。ゲーム層では使用しない。
		/// </remarks>
		/// <returns>スプライトバッチ</returns>
	DirectX::SpriteBatch* GetSpriteBatch() const
	{
		return m_spriteBatch.get();
	}
	/// <summary>
	/// SpriteFontの取得。
	/// </summary>
	/// <remarks>
	/// エンジン内部で使用されます。ゲーム層では使用しない。
	/// </remarks>
	/// <returns>スプライトフォント</returns>
	DirectX::SpriteFont* GetSpriteFont() const
	{
		return m_spriteFont.get();
	}

	/// <summary>
	/// ポストエフェクトこDrawを呼ぶ。
	/// </summary>
	void DrawPostEffect()
	{
		m_postEffect.Draw();
	}

	/// <summary>
/// レンダリングターゲットの切り替え。
/// </summary>
/// <param name="renderTarget">レンダリングターゲット</param>
/// <param name="viewport">ビューポート</param>
	void ChangeRenderTarget(RenderTarget* renderTarget, D3D11_VIEWPORT* viewport);
	void ChangeRenderTarget(ID3D11RenderTargetView* renderTarget, ID3D11DepthStencilView* depthStensil, D3D11_VIEWPORT* viewport);

private:
	D3D_FEATURE_LEVEL		m_featureLevel;				//Direct3D デバイスのターゲットとなる機能セット。
	ID3D11Device*			m_pd3dDevice = NULL;		//D3D11デバイス。
	IDXGISwapChain*			m_pSwapChain = NULL;		//スワップチェイン。
	ID3D11DeviceContext*	m_pd3dDeviceContext = NULL;	//D3D11デバイスコンテキスト。
	ID3D11RenderTargetView* m_backBuffer = NULL;		//バックバッファ。
	ID3D11RasterizerState*	m_rasterizerState = NULL;	//ラスタライザステート。
	ID3D11Texture2D*		m_depthStencil = NULL;		//デプスステンシル。
	ID3D11DepthStencilView* m_depthStencilView = NULL;	//デプスステンシルビュー。

	PostEffect m_postEffect;							//ポストエフェクト。

	std::unique_ptr<DirectX::SpriteBatch>	m_spriteBatch;				//スプライトバッチ。
	std::unique_ptr<DirectX::SpriteFont>	m_spriteFont;				//スプライトフォント。

};

extern GraphicsEngine* g_graphicsEngine;			//グラフィックスエンジン