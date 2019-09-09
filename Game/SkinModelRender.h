#pragma once

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
		int numAnimationClips = 0);

	void InitAnimation(AnimationClip* animationClips, int numAnimationClips);

	void PlayAnimation(int animNo, float interpolateTime = 0.0f)
	{
		m_animation.Play(animNo, interpolateTime);
	}

	/// <summary>
	/// ���W�̐ݒ�B
	/// </summary>
	/// <param name="position">���W</param>
	void SetPosition(const CVector3& position)
	{
		m_position = position;
	}
	
	/// <summary>
	/// ��]��ݒ�B
	/// </summary>
	/// <param name="rotation">��]</param>
	void SetRotation(const CQuaternion& rotation)
	{
		m_rotation = rotation;
	}
	
	/// <summary>
	/// �g�嗦��ݒ�B
	/// </summary>
	/// <param name="scale">�g�嗦</param>
	void SetScale(const CVector3& scale)
	{
		m_scale = scale;
	}

private:

	int m_numAnimationClips = 0;

	const char* m_psmain;
	const char* m_vsmain;

	CVector3 m_position = CVector3::Zero();
	CVector3 m_scale = CVector3::One();

	CQuaternion m_rotation = CQuaternion::Identity();

	Animation m_animation;
	AnimationClip* m_animationClips = nullptr;

	SkinModel m_skinModel;
};
