#pragma once

#include "Skeleton.h"

/*!
*@brief	FBXの上方向。
*/
enum EnFbxUpAxis {
	enFbxUpAxisY,		//Y-up
	enFbxUpAxisZ,		//Z-up
};

const int directionLightNum = 1;		//ディレクションライトの数。(これを変えるときはシェーダー側も変更してあげる必要がある)。


struct DirectionLight {
	CVector4 direction[directionLightNum];	//ディレクションライトの向き。
	CVector4 color[directionLightNum];		//ディレクションライトの色。
	CVector3 eyePos;
	float specPos;
};


/// <summary>
/// ディレクションライト素材。
/// </summary>
/// <remarks>
/// direction = ライトの方向。
/// color = ライトの色。
/// </remarks>
struct LightConstantBuffer
{
	DirectionLight		directionLight;		//ディレクションライト。
	CVector3			eyePos;				//カメラの視点。
	float				specPow;			//スペキュラライトの絞り。
	CVector3			environmentpow;		//環境光の強さ。
};

/*!
*@brief	スキンモデルクラス。
*/
class SkinModel
{
public:
	//メッシュが見つかったときのコールバック関数。
	using OnFindMesh = std::function<void(const std::unique_ptr<DirectX::ModelMeshPart>&)>;
	/*!
	*@brief	デストラクタ。
	*/
	~SkinModel();
	
	/*!
	*@brief	初期化。
	*@param[in]	filePath		ロードするcmoファイルのファイルパス。
	*@param[in] enFbxUpAxis		fbxの上軸。デフォルトはenFbxUpAxisZ。
	*/
	void Init(const wchar_t* filePath, /*EnFbxUpAxis enFbxUpAxis,*/ const char* entryPS, const char* entryVS/*, bool ShadowReciever*/);

	/// <summary>
	/// モデルをワールド座標系に変換するためのワールド行列を更新。
	/// </summary>
	/// <param name="position">モデルの座標</param>
	/// <param name="rotation">モデルの回転</param>
	/// <param name="scale">モデルの拡大率</param>
	void UpdateWorldMatrix(CVector3 position, CQuaternion rotation, CVector3 scale);

	/// <summary>
	/// ボーンを検索。
	/// </summary>
	/// <param name="boneName">ボーンの名前</param>
	/// <returns>見つかったボーン。else見つからなかった場合はnullを返す</returns>
	Bone* FindBone(const wchar_t* boneName)
	{
		int boneId = m_skeleton.FindBoneID(boneName);
		return m_skeleton.GetBone(boneId);
	}
	/*!
	*@brief	モデルを描画。
	*@param[in]	viewMatrix		カメラ行列。
	*  ワールド座標系の3Dモデルをカメラ座標系に変換する行列です。
	*@param[in]	projMatrix		プロジェクション行列。
	*  カメラ座標系の3Dモデルをスクリーン座標系に変換する行列です。
	*/
	/// <summary>
	/// モデルを描画。
	/// </summary>
	/// <param name="renderMode">レンダリングモード</param>
	/// <param name="viewMatrix">カメラ行列(ワールド座標系の3Dモデルをカメラ座標系に変換する行列)</param>
	/// <param name="projMatrix">プロジェクション行列(カメラ座標系の3Dモデルをスクリーン座標系に変換する行列)</param>
	void Draw(EnRenderMode renderMode, CMatrix viewMatrix, CMatrix projMatrix );

	/// <summary>
	/// スケルトンの取得。
	/// </summary>
	/// <returns>スケルトン</returns>
	Skeleton& GetSkeleton()
	{
		return m_skeleton;
	}

	/// <summary>
	/// メッシュの検索。
	/// </summary>
	/// <param name="onFindMesh">メッシュが見つかった時のコールバック関数</param>
	void FindMesh(OnFindMesh onFindMesh) const
	{
		for (auto& modelMeshs : m_modelDx->meshes) {
			for (std::unique_ptr<DirectX::ModelMeshPart>& mesh : modelMeshs->meshParts) {
				onFindMesh(mesh);
			}
		}
	}

	/// <summary>
	/// ディレクションライトの初期化。
	/// </summary>
	void InitDirectionLight();

	/// <summary>
	/// シャドウマップ
	/// </summary>
	/// <param name="srv"></param>
	void SetShadowMap(ID3D11ShaderResourceView* srv) {
		m_shadowMapSRV = srv;
	}

	/// <summary>
	/// マテリアルに対してクエリを行う。
	/// </summary>
	/// <param name="func">お問い合わせ関数</param>
	void QueryMaterials(std::function<void(SkinModel*)> func)
	{
		m_modelDx->UpdateEffects([&](DirectX::IEffect* material) {
			func(reinterpret_cast<SkinModel*>(material));
		});
	}

	/*!
	*@brief	SRVのレジスタ番号。
	*/
	enum EnSkinModelSRVReg {
		enSkinModelSRVReg_DiffuseTexture = 0,		//!<ディフューズテクスチャ。
		enSkinModelSRVReg_BoneMatrix,				//!<ボーン行列。
	};

	/// <summary>
	/// シャドウフラグを設定する。
	/// </summary>
	/// <param name="flag">シャドウレシーバーフラグ</param>
	void SetShadowReciever(bool flag) {
		m_isShadowReciever = flag;
	}

private:
	/*!
	*@brief	サンプラステートの初期化。
	*/
	void InitSamplerState();
	/*!
	*@brief	定数バッファの作成。
	*/
	void InitConstantBuffer();
	/*!
	*@brief	スケルトンの初期化。
	*@param[in]	filePath		ロードするcmoファイルのファイルパス。
	*/
	void InitSkeleton(const wchar_t* filePath);

private:
	//定数バッファ。
	struct SVSConstantBuffer {
		CMatrix mWorld;			//ワールド行列。	
		CMatrix mView;			//ビュー行列。
		CMatrix mProj;			//プロジェクション行列。
		CMatrix mLightView;		//todo ライトビュー行列。
		CMatrix mLightProj;		//todo ライトプロジェクション行列。
		int isShadowReciever;
	};

	bool m_isShadowReciever = true;			//シャドウレシーバーフラグ。

	EnFbxUpAxis			m_enFbxUpAxis = enFbxUpAxisZ;	//!<FBXの上方向。
	ID3D11Buffer*		m_cb = nullptr;					//!<定数バッファ。
	Skeleton			m_skeleton;						//!<スケルトン。
	CMatrix				m_worldMatrix;					//!<ワールド行列。
	DirectX::Model*		m_modelDx;						//!<DirectXTKが提供するモデルクラス。
	ID3D11SamplerState* m_samplerState = nullptr;		//!<サンプラステート。
	ID3D11Buffer*		m_lightConstantBuffer = nullptr;//ライト用の定数バッファ。
	DirectionLight		m_directionLight;				//ディレクションライト。
	ID3D11ShaderResourceView* m_shadowMapSRV = nullptr;

//	const int directionLightNum = 1;		//ディレクションライトの数。

	const char* m_vsmain;
	const char* m_psmain;

};

