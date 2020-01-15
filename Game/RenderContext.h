#pragma once
#include "RenderTarget.h"
#include <stack>
class RenderContext
{
public:
	RenderContext();
	~RenderContext();

	/// <summary>
	/// 現在のレンダリングステートをスタックにプッシュ。
	/// </summary>
	void PushRenderState()
	{
		m_renderStateStack.push(m_currentRenderState);
	}

	/// <summary>
	/// スタックに退避したレンダリングステートをポップ。
	/// </summary>
	/// <param name="isSetRenderSyayeToRenderPipline">ポップしたレンダリングステートをレンダリングパイプラインに設定</param>
	void PopRenderState(bool isSetRenderSyayeToRenderPipline)
	{
		m_currentRenderState = m_renderStateStack.top();		//現在のレンダリングステートをスタックの先頭に変更。
		m_renderStateStack.pop();
		if (isSetRenderSyayeToRenderPipline){
			m_pD3DDeviceContext->OMSetBlendState(m_currentRenderState.blendState, 0, 0xFFFFFFFF);
			m_pD3DDeviceContext->RSSetState(m_currentRenderState.rasterrizerState);
			m_pD3DDeviceContext->OMSetDepthStencilState(m_currentRenderState.depthStencilState, 0);
		}
	}


private:
	/// <summary>
	/// 各種レンダリングステート。
	/// </summary>
	struct SRenderState {
		ID3D11DepthStencilState* depthStencilState = nullptr;	//現在のデプスステンシルステート。
		ID3D11RasterizerState* rasterrizerState = nullptr;		//現在のラスタライザステート。
		ID3D11BlendState* blendState = nullptr;					//現在のブレンドステート。
	};

	/// <summary>
	/// レンダリングターゲット。
	/// </summary>
	struct SRenderTarget {
		RenderTarget* renderTargets[8] = { nullptr };
		unsigned int numRenderTargetViews = 0;
	};
	ID3D11DeviceContext* m_pD3DDeviceContext = nullptr;			//描画コマンドを積んでいくコンテキスト。

	SRenderState m_currentRenderState;				//現在のレンダリングステート。
	std::stack<SRenderState> m_renderStateStack;	//レンダリングステートのスタック。
	std::stack<SRenderTarget> m_renderTargetStack;	//レンダリングターゲットのスタック。

};

