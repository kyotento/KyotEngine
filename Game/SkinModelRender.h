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

	void Init(const wchar_t* filePath,
		AnimationClip* animationClips = nullptr,
		int numAnimationClips = 0, const char* psmain = "PSMain", const char* vsmain = "VSMain");

	void InitAnimation(AnimationClip* animationClips, int numAnimationClips);

	void PlayAnimation(int animNo, float interpolateTime = 0.0f)
	{
		m_animation.Play(animNo, interpolateTime);
	}

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
	/// スキンモデルを持ってくる。
	/// </summary>
	/// <returns>スキンモデル</returns>
	SkinModel& GetSkinModel()
	{
		return m_skinModel;
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

	int m_numAnimationClips = 0;
	bool m_isShadowCaster = true;		//シャドーキャスターフラグ。

	const char* m_psmain;
	const char* m_vsmain;

	CVector3 m_position = CVector3::Zero();
	CVector3 m_scale = CVector3::One();

	CQuaternion m_rotation = CQuaternion::Identity();

	Animation m_animation;
	AnimationClip* m_animationClips = nullptr;

	SkinModel m_skinModel;
};
