#pragma once
#include "ShadowMap.h"

class SkinModelRender : public GameObject
{
public:
	SkinModelRender();
	~SkinModelRender();

	bool Start();
	void Update();
	void Render();
	void RenderAfterPostEffect();

	/// <summary>
	/// 初期化。
	/// </summary>
	/// <param name="filePath">3Dモデルのファイルパス</param>
	/// <param name="animationClips">アニメーション</param>
	/// <param name="numAnimationClips">アニメーションの数</param>
	/// <param name="psmain"></param>
	/// <param name="vsmain">頂点シェーダー</param>
	/// <param name="drawAfterPostEffect">2Dとして描画するかどうか</param>
	/// <param name="SetShadowReciever">影をかけるかどうか</param>
	/// <remarks>
	/// drawAfterPostEffectをtrueにした場合、そのスキンモデルの回転は初期化してはならない
	/// (してもいいけど2Dとしては表示されない。)
	/// </remarks>
	void Init(const wchar_t* filePath,
		AnimationClip* animationClips = nullptr,
		int numAnimationClips = 0,
		const char* psmain = "PSMain", const char* vsmain = "VSMain", 
		bool drawAfterPostEffect = false, bool SetShadowReciever = true);

	/// <summary>
	/// 法線マップの初期化
	/// </summary>
	/// <param name="filePath">法線マップのファイルパス</param>
	/// <remarks>
	/// 初期化を行った場合のみ処理が行われる。
	/// </remarks>
	void InitNormalMap(const wchar_t* filePath);

	/// <summary>
	/// スペキュラマップの初期化。
	/// </summary>
	/// <param name="filePath">スペキュラマップのファイルパス</param>
	/// <remarks>
	/// 初期化を行った場合のみ処理が行われる。
	/// </remarks>
	void InitSpecMap(const wchar_t* filePath);

	/// <summary>
	/// アニメーションの初期化。
	/// </summary>
	/// <param name="animationClips">アニメーション</param>
	/// <param name="numAnimationClips">アニメーションの数</param>
	void InitAnimation(AnimationClip* animationClips, int numAnimationClips);

	/// <summary>
	/// アニメーション。
	/// </summary>
	/// <param name="animNo">アニメーションの数</param>
	/// <param name="interpolateTime">切り替え時間</param>
	void PlayAnimation(int animNo, float interpolateTime = 0.0f)
	{
		m_animation.Play(animNo, interpolateTime);
	}

	/// <summary>
	/// m_drawAfterPostEffectを設定する。
	/// </summary>
	/// <param name="drawAfterPostEffect">ポストエフェクトの後に書くか</param>
	void ChangeDrawAfterPostEffect(bool drawAfterPostEffect);

	/// <summary>
	/// 座標の設定。
	/// </summary>
	/// <param name="position">座標</param>
	void SetPosition(const CVector3& position)
	{
		m_position = position;
	}
	
	/// <summary>
	/// 回転を設定。
	/// </summary>
	/// <param name="rotation">回転</param>
	void SetRotation(const CQuaternion& rotation)
	{
		m_rotation = rotation;
	}
	
	/// <summary>
	/// 拡大率を設定。
	/// </summary>
	/// <param name="scale">拡大率</param>
	void SetScale(const CVector3& scale)
	{
		m_scale = scale;
	}

	/// <summary>
	/// UVスクロールの移動値を設定。
	/// </summary>
	/// <param name="u">テクスチャのX座標</param>
	/// <param name="v">テクスチャのY座標</param>
	void UVScroll(float u, float v);

	/// <summary>
	/// UVスクロールの移動値とタイマーを設定。
	/// </summary>
	/// <param name="u">テクスチャのX座標</param>
	/// <param name="v">テクスチャのY座標</param>
	/// <param name="time">設定したUV値に到達するまでの時間</param>
	void UVScroll(float u, float v, float time);

	/// <summary>
	/// スキンモデルを持ってくる。
	/// </summary>
	/// <returns>スキンモデル</returns>
	SkinModel& GetSkinModel()
	{
		return m_skinModel;
	}

	/// <summary>
	/// スペキュラの強さを設定する。
	/// </summary>
	/// <param name="specPow">スペキュラの強さを設定</param>
	void SetSpecPower(float specPow)
	{
		m_skinModel.SetSpecPower(specPow);
	}

	/// <summary>
	/// シャドーキャスターフラグをセットする。
	/// </summary>
	/// <param name="flag"></param>
	void SetShadowCasterFlag(bool flag)
	{
		m_isShadowCaster = flag;
	}


private:

	int m_numAnimationClips = 0;			//アニメーションの数。
	bool m_isShadowCaster = true;			//シャドーキャスターフラグ。
	bool m_drawAfterPostEffect = false;		//ポストエフェクトの後に書くか。

	const char* m_psmain;
	const char* m_vsmain;

	CVector2 m_uv = CVector2::Zero();						//テクスチャのUV値。

	CVector3 m_position = CVector3::Zero();					//座標。
	CVector3 m_scale = CVector3::One();						//拡大率。	

	CQuaternion m_rotation = CQuaternion::Identity();		//回転

	Animation m_animation;									//アニメーション。
	AnimationClip* m_animationClips = nullptr;				//アニメーションクリップ。

	SkinModel m_skinModel;
};
