/// <summary>
/// �K�E�V�A���u���[�B
/// </summary>
#pragma once
#include "ConstantBufferGPU.h"
#include "RenderTarget.h"

class PostEffect;
class GaussianBlur
{
public:
	GaussianBlur();
	~GaussianBlur();

	/// <summary>
	/// �������B
	/// </summary>
	/// <param name="srtTextureSRV">�e�N�X�`��(�u���[��������)��SRV</param>
	/// <param name="blurPow">�u���[�̋���</param>
	void Init(ID3D11ShaderResourceView* srtTextureSRV, float blurPow);

	/// <summary>
	/// �u���[�̏d�ݍX�V�B
	/// </summary>
	void UpdateWeights();

	/// <summary>
	/// �u���[�̎��s�B
	/// </summary>
	/// <param name="postEffect">
	/// �|�X�g�G�t�F�N�g�̃C���X�^���X�B
	/// �S��ʕ`��̋@�\���g���B
	/// </param>
	/// <remarks>
	/// Init�֐����Ăяo������Ŏ��s����悤�ɁB
	/// </remarks>
	void Execute(PostEffect& postEffect);

	/// <summary>
	/// �u���[�����������ʂ̃e�N�X�`��SRV���擾�B
	/// </summary>
	/// <returns></returns>
	ID3D11ShaderResourceView* GetResultTextureSRV()
	{
		return m_renderTarget[enRenderTarget_Y].GetRenderTargetSRV();
	}
private:

	/// <summary>
	/// �����_�����O�^�[�Q�b�g�B
	/// </summary>
	enum EnRenderTarget {
		enRenderTarget_X,		//X�u���[�̏������ݐ�ƂȂ郌���_�����O�^�[�Q�b�g�B
		enRenderTarget_Y,		//Y�u���[�̏������ݐ�ƂȂ郌���_�����O�^�[�Q�b�g�B
		enRenderTargetNum		//�����_�����O�^�[�Q�b�g�̐��B
	};

	static const int NUM_WEIGHTS = 8;	//�J�E�X�t�B���^�̏d�݂̐��B
	/// <summary>
	/// �u���[�p�̃p�����[�^�o�b�t�@�B
	/// </summary>
	/// <remarks>
	/// �����ύX������AAssets/shader/GaussianBlur.fx��CBBlur�̒��g���ύX����B
	/// </remarks>
	struct SBlurParam {
		float weights[NUM_WEIGHTS];
	};

	unsigned int m_srcTextureWidth = 0;						//�\�[�X�e�N�X�`���̕��B
	unsigned int m_srcTextureHeight = 0;					//�\�[�X�e�N�X�`���̍����B

	float m_blurPower = 25.0f;								//�u���[�̋����B

	bool m_isInit = false;									//�������������ۂ��B

	RenderTarget m_renderTarget[enRenderTargetNum];			//�����_�����O�^�[�Q�b�g�B

	ID3D11ShaderResourceView* m_srcTextureSRV = nullptr;	//�\�[�X�e�N�X�`����SRV

	Shader m_vsXBlur;							//X�u���[�p�̒��_�V�F�[�_�[�B
	Shader m_vsYBlur;							//Y�u���[�p�̒��_�V�F�[�_�[�B
	Shader m_psBlur;							//�u���[�p�̃s�N�Z���V�F�[�_�[�B

	SBlurParam m_blurParam;						//�u���[�p�̃p�����[�^�B
	ConstantBufferGPU m_blurCbGpu;				//�u���[�p�̒萔�o�b�t�@(GPU��)

};

