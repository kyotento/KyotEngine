#pragma once

#include "Effect.h"
class Sprite
{
public:

	Sprite();
	~Sprite();

	static const CVector2 Default_Pivot;		//デフォルトのピボット。

	//頂点バッファの座標。
	struct SVertex {
		float position[4];
		float uv[2];
	};

	//定数バッファ。
	struct ConstantBuffer {
		CMatrix WVP;
		CVector4 mulCol;
	};

	void Init(ID3D11ShaderResourceView* srv, float w, float h);

	//初期化。
	/*
		TextureFilePath = テクスチャのファイルパス。
		w               = 画僧の幅。
		h               = 画僧の高さ。
	*/
	void Init(const wchar_t* TextureFilePath, float w, float h);


	//描画の更新処理。
	/*
		trans = 平行移動。
		rot   = 回転。
		scale = 拡大。
		pivot = 基点。 { 0 , 0 }     画像の左上。
		               { 0.5 , 0.5 } 画面の中心。 
					   { 1 , 1 }     画面の右下。
	*/
	void Update(const CVector3& trans, const CQuaternion& rot, const CVector3& scale, CVector2 pivot = { 0.5f, 0.5f });

	void Draw();

	//定数バッファの初期化。
	void InitConstantBuffer();

	CVector2 m_size = CVector2::Zero();            //画像のサイズ。

	CMatrix	m_world = CMatrix::Identity();			//ワールド行列。

	ID3D11Buffer* m_vertexBuffer = NULL;           //頂点バッファ。
	ID3D11Buffer* m_indexBuffer = NULL;            //インデックスバッファ。
	Effect m_effect;                               //エフェクト。
	ID3D11RenderTargetView* m_texture = NULL;      //テクスチャ。
	ID3D11SamplerState* m_samplerState = NULL;     //サンプラーステート。


	//頂点バッファの初期化。
	void InitVertexBuffer(float w, float h);

	//インデックスバッファの初期化。
	void InitIndexBuffer();

	//サンプルステートの初期化。
	void InitSampleState();

};

