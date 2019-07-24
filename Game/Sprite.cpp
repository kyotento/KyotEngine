#include "stdafx.h"
#include "Sprite.h"


Sprite::Sprite()
{
}


Sprite::~Sprite()
{

}

//頂点バッファの初期化。
void Sprite::InitVertexBuffer(float w, float h)
{

	//座標の設定。

	float halfW = w * 0.5f;
	float halfH = h * 0.5f;
	SVertex vertex[4] = {
		//頂点１
		{
			//座標　position[4]
			-halfW,  -halfH, 0.0f, 1.0f,
			//UV座標 uv[2]
			0.0f, 1.0f
		},
		//頂点２
		{
			//座標　position[4]
			halfW, -halfH, 0.0f, 1.0f,
			//UV座標 uv[2]
			1.0f, 1.0f
		},
		//頂点３
		{
			//座標　position[4]
			-halfW,  halfH, 0.0f, 1.0f,
			//UV座標 uv[2]
			0.0f, 0.0f
		},
		//頂点４
		{
			//座標　position[4]
			halfW,  halfH, 0.0f, 1.0f,
			//UV座標 uv[2]
			1.0f, 0.0f
		},
	};

	//↑で定義した頂点を使う。
	//頂点バッファを作成するためにはD3D11_BUFFER_DESCとD3D11_SUBRESOURCE_DATAを設定する必要がある。

	//D3D11_BUFFER_DESC 設定開始。
	D3D11_BUFFER_DESC DBD;
	DBD.ByteWidth = sizeof(vertex);       //頂点バッファのサイズ。(上で作ったやつ)。
	DBD.Usage = D3D11_USAGE_DEFAULT;      //読み書き方法。デフォルトで。
	DBD.CPUAccessFlags = 0;               //そのまんまCPUアクセスフラグ。アクセス不要の場合は０。
	DBD.MiscFlags = 0;                    //その他フラグ。未使用は０。
	DBD.StructureByteStride = 0;          //バッファが構造化バッファを表す場合の、バッファ構造内の各要素のサイズ（バイト単位）。

	
}

//インデックスバッファの初期化。
void Sprite::InitIndexBuffer()
{
	//頂点番号。
	int index[6] = {
	0,1,2,		//三角形一つ目
	2,1,3		//三角形二つ目
	};

}

//サンプラステートの初期化。
void Sprite::InitSampleState()
{

}

//
void Sprite::InitConstantBuffer()
{
	D3D11_BUFFER_DESC desc;
	// 頂点バッファの初期化設定
	desc.ByteWidth = (((sizeof(ConstantBuffer) - 1) / 16) + 1) * 16;  //バッファのサイズ。
	desc.Usage = D3D11_USAGE_DEFAULT;                                 //バッファの読み書き方法。
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;                      //バッファをパイプラインにどのようにバインドするかを指定。
	desc.CPUAccessFlags = 0;                                          //そのまんまCPUアクセスフラグ。アクセス不要の場合は０。
	desc.MiscFlags = 0;                                               //その他フラグ。未使用は０。
	desc.StructureByteStride = 0;                                     //バッファが構造化バッファを表す場合の、バッファ構造内の各要素のサイズ（バイト単位）。
}

//Init関数。
void Sprite::Init(const wchar_t* TextureFilePath, float w, float h)
{
	//頂点バッファの初期化。
	InitVertexBuffer(w,h);
	//インデックスバッファの初期化。
	InitIndexBuffer();
	//サンプラステートの初期化。
	InitSampleState();
	//エフェクトファイルのロード。
	//m_effect.Load("Assets/shader/");


}