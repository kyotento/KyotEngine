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

	camera2d.SetPosition(m_enUpdateProjMatrixFunc_OrthoPosition);
}


Sprite::~Sprite()
{
}


const CVector2	Sprite::DEFAULT_PIVOT = { 0.5f, 0.5f };

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
	ZeroMemory(&DSD, sizeof(DSD));
	DSD.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;			//U方向ラップ。
	DSD.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;			//V方向ラップ。
	DSD.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;			//W方向ラップ。
	DSD.MaxAnisotropy = 1;
	DSD.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;		//テクスチャファイル。

	//サンプラーステートの作成。
	HRESULT hr=g_graphicsEngine->GetD3DDevice()->CreateSamplerState(&DSD, &m_samplerState);

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

	//定数バッファの作成。
	g_graphicsEngine->GetD3DDevice()->CreateBuffer(&desc, NULL, &m__cb);

}

//ブレンドステート。
void Sprite::BlendState()
{
	//ブレンドステートオブジェクトの作成。
	D3D11_BLEND_DESC blendDesc;

	ZeroMemory(&blendDesc, sizeof(blendDesc));
	blendDesc.AlphaToCoverageEnable = true;		//描画ターゲットにピクセル値を設定するときにα値を使用するか。

	ID3D11Device* pd3d = g_graphicsEngine->GetD3DDevice();
	blendDesc.RenderTarget[0].BlendEnable = true;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_RED | D3D11_COLOR_WRITE_ENABLE_BLUE | D3D11_COLOR_WRITE_ENABLE_GREEN;
	pd3d->CreateBlendState(&blendDesc, &pBlendState);
	{
		{
			{
				D3D11_DEPTH_STENCIL_DESC desc;
				ZeroMemory(&desc, sizeof(desc));
				ID3D11Device* pd3d = g_graphicsEngine->GetD3DDevice();
				desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
				desc.DepthFunc = D3D11_COMPARISON_LESS;
				desc.DepthEnable = true;
				desc.StencilEnable = false;
				pd3d->CreateDepthStencilState(&desc, &zspriteRender);
			}
			{
				D3D11_DEPTH_STENCIL_DESC desc;
				ZeroMemory(&desc, sizeof(desc));
				ID3D11Device* pd3d = g_graphicsEngine->GetD3DDevice();
				desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
				desc.DepthFunc = D3D11_COMPARISON_LESS;
				desc.DepthEnable = false;
				desc.StencilEnable = false;
				pd3d->CreateDepthStencilState(&desc, &spriteRender);
			}
		}
		{
			D3D11_RASTERIZER_DESC desc = {};
			ID3D11Device* pd3d = g_graphicsEngine->GetD3DDevice();
			desc.CullMode = D3D11_CULL_NONE;
			desc.FillMode = D3D11_FILL_SOLID;
			desc.DepthClipEnable = true;
			desc.MultisampleEnable = true;
			pd3d->CreateRasterizerState(&desc, &rspriteRender);
		}
	}
}

void Sprite::CommonProcessing(float w, float h)
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
		"VSMain",
		Shader::EnType::VS	//頂点シェーダー。
	);
	//ピクセルシェーダーをロード。
	m_psShader.Load(
		"Assets/shader/sprite.fx",
		"PSMain",
		Shader::EnType::PS	//ピクセルシェーダー。
	);

	//定数バッファを初期化。
	InitConstantBuffer();
}


void Sprite::RasterizerState()
{
	
	D3D11_RASTERIZER_DESC rasterizerDesc =
	{
		D3D11_FILL_SOLID, // 
		D3D11_CULL_NONE,      // 
		FALSE,
		0,
		0.0f,
		FALSE,
		FALSE,
		FALSE,
		FALSE,
		FALSE
	};

	g_graphicsEngine->GetD3DDevice()->CreateRasterizerState(&rasterizerDesc, &rasterizerState);

}

//Init関数。シェーダーロード用。
void Sprite::Init(ID3D11ShaderResourceView* srv, float w, float h)
{
	
	CommonProcessing(w, h);

	m_texture = srv;
	if (m_texture != nullptr) {
		m_texture->AddRef();
	}
	//定数バッファを初期化。
	InitConstantBuffer();

	//ブレンドステート。
	BlendState();

	//ラスタライザステート。
	RasterizerState();
}

//Init関数。テクスチャロード。
void Sprite::Init(const wchar_t* TextureFilePath, float w, float h)
{
	////画像サイズ。
	//m_size.x = w;
	//m_size.y = h;

	////頂点バッファの初期化。
	//InitVertexBuffer(w, h);
	////インデックスバッファの初期化。
	//InitIndexBuffer();
	////サンプラステートの初期化。
	//InitSamplerState();

	CommonProcessing(w, h);

	//ファイル名を使って、テクスチャをロードして、ShaderResrouceViewを作成する。
	HRESULT hr = DirectX::CreateDDSTextureFromFileEx(
		g_graphicsEngine->GetD3DDevice(),	//D3Dデバイス
		TextureFilePath,					//読み込むテクスチャのファイルパス。
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

	//ブレンドステート。
	BlendState();

	//ラスタライザステート。
	RasterizerState();

}

//描画処理。
void Sprite::Draw(Camera* camera)
{		

	unsigned int vertexSize = sizeof(SVertex);
	unsigned int offset = 0;
	GraphicsEngine* ge = g_graphicsEngine;
	ge->GetD3DDeviceContext()->IASetVertexBuffers(
		0,
		1,
		&m_vertexBuffer,
		&vertexSize,
		&offset
	);
	ge->GetD3DDeviceContext()->IASetIndexBuffer(
		m_indexBuffer,
		DXGI_FORMAT_R32_UINT,
		0
	);

	//デバイスコンテキストを取得。
	auto deviceContext = g_graphicsEngine->GetD3DDeviceContext();

	//頂点シェーダーを設定。
	deviceContext->VSSetShader(
		(ID3D11VertexShader*)m_vsShader.GetBody(),	//頂点シェーダー。
		NULL,										//NULLでいい。
		0											//0でいい。
	);
	//ピクセルシェーダーを設定。
	deviceContext->PSSetShader(
		(ID3D11PixelShader*)m_psShader.GetBody(),	//ピクセルシェーダー。
		NULL,										//NULLでいい。
		0											//0でいい。
	);
	//頂点レイアウトを設定。
	deviceContext->IASetInputLayout(m_vsShader.GetInputLayout());

	float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	g_graphicsEngine->GetD3DDeviceContext()->OMSetBlendState(pBlendState, blendFactor, 0xffffffff);
	g_graphicsEngine->GetD3DDeviceContext()->PSSetShaderResources(0, 1, &m_texture);
	g_graphicsEngine->GetD3DDeviceContext()->PSSetSamplers(0, 1, &m_samplerState);
	g_graphicsEngine->GetD3DDeviceContext()->RSSetState(rspriteRender);
	//deviceContext->RSSetState(rasterizerState);

	/*a = m_camera.GetSetUpdateCameraMatrix();*/

	ConstantBuffer cb;
	cb.WVP = m_world;

	//g_graphicsEngine->GetD3DDeviceContext()->OMSetDepthStencilState(spriteRender, 0);
	//cb.WVP.Mul(cb.WVP, camera2d.GetViewMatrix());
	//cb.WVP.Mul(cb.WVP, camera2d.GetProjectionMatrix());

	g_graphicsEngine->GetD3DDeviceContext()->OMSetDepthStencilState(zspriteRender, 0);
	cb.WVP.Mul(cb.WVP, camera->GetViewMatrix());
	cb.WVP.Mul(cb.WVP, camera->GetProjectionMatrix());
	
	cb.mulCol = m_mulCol;
	ge->GetD3DDeviceContext()->UpdateSubresource(m__cb, 0, NULL, &cb, 0, 0);
	ge->GetD3DDeviceContext()->VSSetConstantBuffers(0, 1, &m__cb);
	ge->GetD3DDeviceContext()->PSSetConstantBuffers(0, 1, &m__cb);
	ge->GetD3DDeviceContext()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	ge->GetD3DDeviceContext()->DrawIndexed(
		6,
		0,
		0
	);


}