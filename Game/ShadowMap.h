#pragma once 

#include "RenderTarget.h"

class ShadowMap
{
public:
	ShadowMap();
	~ShadowMap();

	/// <summary>
/// ���C�g�r���[�s����擾�B
/// </summary>
/// <returns></returns>
	CMatrix GetLighViewMatrix()
	{
		return m_lightViewMatrix;
	}
	/// <summary>
	/// ���C�g�v���W�F�N�V�����s����擾�B
	/// </summary>
	/// <returns></returns>
	CMatrix GetLightProjMatrix()
	{
		return m_lightProjMatrix;
	}

	/// <summary>
	/// �X�V�����B
	/// </summary>
	/// <param name="lightCameraPos">���C�g�J�����̎��_���W</param>
	/// <param name="lightCameraTarget">���C�g�J������p�����_�̍��W</param>
	void Update(CVector3 lightCameraPos, CVector3 lightCameraTarget);

	/// <summary>
	/// �V���h�E�}�b�v�ɕ`�悳���V���h�E�L���X�^�[�B
	/// </summary>
	void RenderToShadowMap();

	/// <summary>
	/// �V���h�E�L���X�^�[��o�^�B
	/// </summary>
	/// <param name="shadowCaster">�V���h�E�L���X�^�[</param>
	void RegistShadowCaster(SkinModel* shadowCaster)
	{
		m_shadowCasters.push_back(shadowCaster);
	}

private:
	CVector3 m_lightCameraPosition = CVector3::Zero();	//���C�g�J�����̎��_�B
	CVector3 m_lightCameraTarget = CVector3::Zero();	//���C�g�J�����̒����_�B
	CMatrix m_lightViewMatrix = CMatrix::Identity();	//���C�g�r���[�s��B
	CMatrix m_lightProjMatrix = CMatrix::Identity();	//���C�g�v���W�F�N�V�����s��B
	RenderTarget m_shadowMapRT;						//�V���h�E�}�b�v��`�悷�郌���_�����O�^�[�Q�b�g�B
	std::vector< SkinModel*> m_shadowCasters;	//�V���h�E�L���X�^�[�̔z��B

};

