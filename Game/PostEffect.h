#pragma once
#include "Bloom.h"

class PostEffect
{
public:
	PostEffect();
	~PostEffect();

	/// <summary>
	/// 更新処理。
	/// </summary>
	void Update();

	/// <summary>
	/// 初期化。
	/// </summary>
	void Init();

	/// <summary>
	/// 描画処理。
	/// </summary>
	void Draw();

	/// <summary>
	/// フルスクリーン描画。
	/// </summary>
	/// <param name="deviceContext">デバイスコンテキスト</param>
	/// <param name="vsShader">頂点シェーダー</param>
	/// <param name="psShader">ピクセルシェーダー</param>
	void DrawFullScreenQuadPrimitive(ID3D11DeviceContext* deviceContext, Shader& vsShader, Shader& psShader);



private:

	/// <summary>
	/// フルスクリーン描画用の四角形プリミティブの初期化。
	/// </summary>
	void InitFullScreenQuadPrimitive();

	Bloom	m_bloom;	//ブルーム。
	//フルスクリーン描画用のメンバ変数。
	ID3D11Buffer*	m_vertexBuffer = nullptr;		//頂点バッファ。
	ID3D11InputLayout* m_inputLayout = nullptr;		//入力レイアウト。

};

