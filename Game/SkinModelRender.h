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
	/// �������B
	/// </summary>
	/// <param name="filePath">3D���f���̃t�@�C���p�X</param>
	/// <param name="animationClips">�A�j���[�V����</param>
	/// <param name="numAnimationClips">�A�j���[�V�����̐�</param>
	/// <param name="psmain"></param>
	/// <param name="vsmain">���_�V�F�[�_�[</param>
	/// <param name="drawAfterPostEffect">2D�Ƃ��ĕ`�悷�邩�ǂ���</param>
	/// <param name="SetShadowReciever">�e�������邩�ǂ���</param>
	/// drawAfterPostEffect��true�ɂ����ꍇ�A���̃X�L�����f���̉�]�͏��������Ă͂Ȃ�Ȃ�(���Ă���������2D�Ƃ��Ă͕\������Ȃ��B)
	void Init(const wchar_t* filePath,
		AnimationClip* animationClips = nullptr,
		int numAnimationClips = 0,
		const char* psmain = "PSMain", const char* vsmain = "VSMain", 
		bool drawAfterPostEffect = false, bool SetShadowReciever = true);

	/// <summary>
	/// �A�j���[�V�����̏������B
	/// </summary>
	/// <param name="animationClips">�A�j���[�V����</param>
	/// <param name="numAnimationClips">�A�j���[�V�����̐�</param>
	void InitAnimation(AnimationClip* animationClips, int numAnimationClips);

	/// <summary>
	/// �A�j���[�V�����B
	/// </summary>
	/// <param name="animNo">�A�j���[�V�����̐�</param>
	/// <param name="interpolateTime">�؂�ւ�����</param>
	void PlayAnimation(int animNo, float interpolateTime = 0.0f)
	{
		m_animation.Play(animNo, interpolateTime);
	}

	/// <summary>
	/// m_drawAfterPostEffect��ݒ肷��B
	/// </summary>
	/// <param name="drawAfterPostEffect">�|�X�g�G�t�F�N�g�̌�ɏ�����</param>
	void ChangeDrawAfterPostEffect(bool drawAfterPostEffect);

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

	/// <summary>
	/// �X�L�����f���������Ă���B
	/// </summary>
	/// <returns>�X�L�����f��</returns>
	SkinModel& GetSkinModel()
	{
		return m_skinModel;
	}

	/// <summary>
	/// �V���h�[�L���X�^�[�t���O���Z�b�g����B
	/// </summary>
	/// <param name="flag"></param>
	void SetShadowCasterFlag(bool flag)
	{
		m_isShadowCaster = flag;
	}


private:

	int m_numAnimationClips = 0;			//�A�j���[�V�����̐��B
	bool m_isShadowCaster = true;			//�V���h�[�L���X�^�[�t���O�B
	bool m_drawAfterPostEffect = false;		//�|�X�g�G�t�F�N�g�̌�ɏ������B

	const char* m_psmain;
	const char* m_vsmain;

	CVector3 m_position = CVector3::Zero();					//���W�B
	CVector3 m_scale = CVector3::One();						//�g�嗦�B	

	CQuaternion m_rotation = CQuaternion::Identity();		//��]

	Animation m_animation;									//�A�j���[�V�����B
	AnimationClip* m_animationClips = nullptr;				//�A�j���[�V�����N���b�v�B

	SkinModel m_skinModel;
};
