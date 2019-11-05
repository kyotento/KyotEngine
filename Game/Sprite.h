#pragma once

#include "Effect.h"
#include "graphics/Shader.h"
#include "graphics/Camera.h"
class Sprite
{
public:

	Sprite();
	~Sprite();

	/// <summary>
	/// defaultのPovot。
	/// </summary>
	static const CVector2	DEFAULT_PIVOT;					//!<ピボット。


	/// <summary>
	/// 頂点バッファの座標
	/// </summary>
	struct SVertex {
		float position[4];
		float uv[2];
	};

	/// <summary>
	/// 定数バッファ
	/// </summary>
	struct ConstantBuffer {
		CMatrix WVP;
		CVector4 mulCol;
	};

	/// <summary>
	/// Init関数で使うものが作られている。
	/// </summary>
	/// <param name="w">幅</param>
	/// <param name="h">高さ</param>
	void CommonProcessing(float w, float h);


	/// <summary>
	/// シェーダーロード
	/// </summary>
	/// <param name="srv">レンダリング中にシェーダーがアクセスできるサブリソースを指定</param>
	/// <param name="w">画像の幅</param>
	/// <param name="h">画像の高さ</param>
	void Init(ID3D11ShaderResourceView* srv, float w, float h);

	/// <summary>
	/// テクスチャロード初期化。
	/// </summary>
	/// <param name="TextureFilePath">テクスチャのファイルパス</param>
	/// <param name="w">画像の幅</param>
	/// <param name="h">画像の高さ</param>
	void Init(const wchar_t* TextureFilePath, float w, float h);

	/// <summary>
	/// 描画の更新処理。
	/// </summary>
	/// <param name="trans">平行移動</param>
	/// <param name="rot">回転</param>
	/// <param name="scale">拡大</param>
	/// <param name="pivot">基点</param>
	///                    { 0 , 0 }     画像の左上。
	///					   { 0.5, 0.5 } 画面の中心。
	///					   { 1 , 1 }     画面の右下。
	void Update(const CVector3& trans, const CQuaternion& rot, const CVector3& scale, CVector2 pivot = DEFAULT_PIVOT);

	/// <summary>
	/// 描画処理。
	/// </summary>
	void Draw(Camera* camera);

	/// <summary>
	/// ブレンドの初期化。
	/// </summary>
	void BlendState();

	/// <summary>
	/// 定数バッファの初期化。
	/// </summary>
	void InitConstantBuffer();

	/// <summary>
	/// ラスタライザステートの設定。
	/// </summary>
	void RasterizerState();

	CVector2 m_size = CVector2::Zero();						//画像のサイズ。

	CMatrix	m_world = CMatrix::Identity();					//ワールド行列。

	Camera::EnUpdateProjMatrixFunc m_cameraMode = Camera::enUpdateProjMatrixFunc_Ortho;
	bool a = 0;

	ID3D11Buffer* m_vertexBuffer = NULL;					  //頂点バッファ。
	ID3D11Buffer* m_indexBuffer = NULL;						  //インデックスバッファ。
	ID3D11DepthStencilState* m_depthStencilState = NULL;
	ID3D11DepthStencilState*	spriteRender = NULL;
	ID3D11DepthStencilState*	zspriteRender = NULL;
	ID3D11BlendState* pBlendState = NULL;					//ブレンドステート。
	ID3D11RasterizerState*	rspriteRender = NULL;
	ID3D11Buffer*				m__cb = nullptr;							//定数バッファ。
	ID3D11RasterizerState* rasterizerState = NULL;			//ラスタライザステート。

	ID3D11ShaderResourceView* m_texture = NULL;				//テクスチャ。
	ID3D11SamplerState* m_samplerState = NULL;				 //サンプラーステート。
	Effect m_effect;										 //エフェクト。
	Shader m_vsShader;										 //頂点シェーダー。
	Shader m_psShader;										 //ピクセルシェーダー。

	CVector4  m_mulCol = { 1.f,1.f,1.f,1.f };
	/// <summary>
	/// 頂点バッファの初期化
	/// </summary>
	/// <param name="w">画像の幅</param>
	/// <param name="h">画像の高さ</param>
	void InitVertexBuffer(float w, float h);

	/// <summary>
	/// インデックスバッファの初期化
	/// </summary>
	void InitIndexBuffer();

	/// <summary>
	/// サンプルステートの初期化
	/// </summary>
	void InitSamplerState();


private:

	CVector3 m_enUpdateProjMatrixFunc_OrthoPosition = { 0.f,0.f,-100.f };

	Camera m_camera;

};

