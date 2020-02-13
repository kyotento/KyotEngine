/// <summary>
/// �u���[���B
/// </summary>
#pragma once
#include "GaussianBlur.h"

class PostEffect;
class Bloom
{
public:
	Bloom();
	~Bloom();

	/// <summary>
	/// �������B
	/// </summary>
	void Init();

	/// <summary>
	/// �P�x���o�p�����_�[�^�[�Q�b�g�̏������B
	/// </summary>
	void InitRenderTarget();

	/// <summary>
	/// �V�F�[�_�[�̏������B
	/// </summary>
	void InitShader();

	/// <summary>
	/// ���u�����f�B���Osy�e�[�g�̏������B
	/// </summary>
	void InitAlphaBlendState();

	/// <summary>
	/// �T���v���[�X�e�[�g�̏������B
	/// </summary>
	void InitSamplerState();

	/// <summary>
	/// �`�揈���B
	/// </summary>
	/// <param name="postEffect">�|�X�g�G�t�F�N�g</param>
	void Draw(PostEffect& postEffect);

private:

	static const int NUM_DOWN_SAMPLE = 4;				//�_�E���T���v�����O�̉񐔁B

	ID3D11SamplerState* m_samplerState = nullptr;		//�T���v���X�e�[�g�B
	ID3D11BlendState* m_disableBlendState = nullptr;	//�A���t�@�u�����f�B���O�𖳌��ɂ���u�����f�B���O�X�e�[�g�B
	ID3D11BlendState* m_finalBlendState = nullptr;		//�ŏI�����p�̃u�����f�B���O�X�e�[�g�B

	Shader m_vs;						//�������Ȃ����_�V�F�[�_�[�B
	Shader m_psLuminance;				//�P�x���o�p�̃s�N�Z���V�F�[�_�[�B
	Shader m_psCombine;					//�ڂ����摜�����p�̃s�N�Z���V�F�[�_�[�B
	Shader m_psFinal;					//�ŏI�����p�̃s�N�Z���V�F�[�_�[�B

	RenderTarget m_luminanceRT;			//�P�x�𒊏o���郌���_�����O�^�[�Q�b�g�B
	RenderTarget m_blurCombineRT;		//�u���[�̉摜���������郌���_�����O�^�[�Q�b�g�B

	GaussianBlur m_gausianBlur[NUM_DOWN_SAMPLE];	//�P�x���ڂ������߂̃K�E�V�A���u���[�B
		
};

