#include "stdafx.h"
#include "Sprite.h"

/// <summary>
/// 2Dを描画するためのクラス
/// </summary>
/// <remarks>
/// 頂点バッファのデータ形式を定義する構造体を宣言。
/// 作成する頂点バッファを「D3D11_BUFFER_DESC」で定義。
/// サブリソースの初期化データを「D3D11_SUBRESOURCE_DATA　構造体」で定義。
///「ID3D11Device::CreateBuffer　メソッド」で頂点バッファを作成。
/// </remarks>

Sprite::Sprite()
{
}


Sprite::~Sprite()
{
}

//更新関数。
void Sprite::Update(const CVector3& trans, const CQuaternion& rot, const CVector3& scale, CVector2 pivot)
{
	//ローカルピボット。
	CVector2 localPivot = pivot;
	localPivot.x -= 0.5f;
	localPivot.y -= 0.5f;
	localPivot.x *= -2.0f;
	localPivot.y *= -2.0f;

	//画像のハーフサイズ。
	CVector2 halfSize = m_size;
	halfSize.x *= 0.5f;
	halfSize.y *= 0.5f;

	CMatrix mPivotTrans;                        //平行移動行列。
	mPivotTrans.MakeTranslation(                //ピボットとSizeを使って平行移動行列の計算。
		{ halfSize.x * localPivot.x, halfSize.y * localPivot.y, 0.0f }
	);

	CMatrix mTrans, mRot, mScale;
	mTrans.MakeTranslation(trans);				//平行移動行列。
	mRot.MakeRotationFromQuaternion(rot);		//回転行列。
	mScale.MakeScaling(scale);					//拡大行列。
	m_world.Mul(mPivotTrans, mScale);           //行列の乗算。
	m_world.Mul(m_world, mRot);
	m_world.Mul(m_world, mTrans);
	
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
	DBD.ByteWidth = sizeof(vertex);             //頂点バッファのサイズ。(上で作ったやつ)。
	DBD.Usage = D3D11_USAGE_DEFAULT;            //読み書き方法。デフォルトで。
	DBD.CPUAccessFlags = 0;                     //そのまんまCPUアクセスフラグ。アクセス不要の場合は０。
	DBD.MiscFlags = 0;                          //その他フラグ。未使用は０。
	DBD.StructureByteStride = 0;                //バッファが構造化バッファを表す場合の、バッファ構造内の各要素のサイズ（バイト単位）。
	DBD.BindFlags = D3D11_BIND_VERTEX_BUFFER;	//これから作成するバッファが頂点バッファであることを指定する。

	//D3D11_SUBRESOURCE_DATA 設定開始。
	D3D11_SUBRESOURCE_DATA DSD;
	DSD.pSysMem = vertex;                       //バッファ、データの初期値。
	DSD.SysMemPitch = 0;                        //メモリのピッチ（バイト数）。
	DSD.SysMemSlicePitch = 0;                   //深度レベル（バイト数）。

	//頂点バッファの作成。
	g_graphicsEngine->GetD3DDevice()->CreateBuffer(&DBD, &DSD, &m_vertexBuffer);
}

//インデックスバッファの初期化。
void Sprite::InitIndexBuffer()
{
	//頂点番号。
	int index[6] = {
	0,1,2,		//三角形一つ目
	2,1,3		//三角形二つ目
	};


	//頂点バッファ同様、インデックスバッファを作成するためにはD3D11_BUFFER_DESCとD3D11_SUBRESOURCE_DATAを設定する必要がある。

	//D3D11_BUFFER_DESC設定。
	D3D11_BUFFER_DESC IDBD;
	IDBD.Usage = D3D11_USAGE_DEFAULT;               //バッファの読み込み（default）。
	IDBD.ByteWidth = sizeof(index);                 //バッファのサイズ。頂点番号数。
	IDBD.BindFlags = D3D11_BIND_INDEX_BUFFER;       //インデックスバッファ。
	IDBD.CPUAccessFlags = 0;                        //CPUアクセスフラグ。
	IDBD.MiscFlags = 0;                             //その他フラグ。
	IDBD.StructureByteStride = 0;                   //構造化バッファの場合、その構造体のサイズ（バイト数）。

	//D3D11_SUBRESOURCE_DATA設定開始。
	D3D11_SUBRESOURCE_DATA IDSD;
	IDSD.pSysMem = index;                           //バッファ、データの初期値。
	IDSD.SysMemPitch = 0;                           //メモリのピッチ。
	IDSD.SysMemSlicePitch = 0;                      //深度レベル。

	//インデックスバッファの作成。
	g_graphicsEngine->GetD3DDevice()->CreateBuffer(&IDBD, &IDSD, &m_indexBuffer);

} 

//サンプラーステートの初期化。(どのようにテクスチャがサンプルされるかを定義)。
void Sprite::InitSamplerState()
{

	D3D11_SAMPLER_DESC DSD;
	DSD.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;			//U方向ラップ。
	DSD.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;			//V方向ラップ。
	DSD.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;			//W方向ラップ。
	DSD.MaxAnisotropy = 1;
	DSD.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;		//テクスチャファイル。

	//サンプラーステートの作成。
	g_graphicsEngine->GetD3DDevice()->CreateSamplerState(&DSD, &m_samplerState);

}

//定数バッファ。cpp側からシェーダに渡す情報を構造体にしたもの。
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

//Init関数。シェーダーロード用。
void Sprite::Init(ID3D11ShaderResourceView* srv, float w, float h)
{
	m_size.x = w;
	m_size.y = h;
	//頂点バッファの初期化。
	InitVertexBuffer(w, h);
	//インデックスバッファの初期化。
	InitIndexBuffer();
	//サンプラステートの初期化。
	InitSamplerState();

	//頂点シェーダーをロード。
	/*
		第一引数はロードするシェーダーソースファイルのファイルパス。
		第二引数はエントリーポイントとなる関数の名前。 
		第三引数はロードしたシェーダーのタイプ。
	*/
	m_vsShader.Load(
		"Assets/shader/sprite.fx",
		"VS",
		Shader::EnType::VS	//頂点シェーダー。
	);
	//ピクセルシェーダーをロード。
	m_psShader.Load(
		"Assets/shader/sprite.fx",
		"PS",
		Shader::EnType::PS	//ピクセルシェーダー。
	);

	//定数バッファを初期化。
	InitConstantBuffer();


	m_texture = srv;
	if (m_texture != nullptr) {
		//m_texture->AddRef();
	}

}

//Init関数。テクスチャロード。
void Sprite::Init(const wchar_t* TextureFilePath, float w, float h)
{
	//画像サイズ。
	m_size.x = w;
	m_size.y = h;

	//頂点バッファの初期化。
	InitVertexBuffer(w, h);
	//インデックスバッファの初期化。
	InitIndexBuffer();
	//サンプラステートの初期化。
	InitSamplerState();

	//ファイル名を使って、テクスチャをロードして、ShaderResrouceViewを作成する。
	HRESULT hr = DirectX::CreateDDSTextureFromFileEx(
		g_graphicsEngine->GetD3DDevice(),	//D3Dデバイス
		L"Assets/modelData/utc_all2.dds",	//読み込むテクスチャのファイルパス。
		0,				                    //テクスチャの最大サイズ。0だとテクスチャサイズがそのまま読み込まれる
		D3D11_USAGE_DEFAULT,		    	//リソースの使用用途。
		D3D11_BIND_SHADER_RESOURCE,	        //リソースのバインド方法。
		0,									//0でよい。
		0,									//0でよい。
		false,								//falseでいい。
		nullptr,							//nullptrでいい。
		&m_texture					        //SRV
	);

	//定数バッファを初期化。
	InitConstantBuffer();


}

//描画処理。
void Sprite::Draw()
{


}