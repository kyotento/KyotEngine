/// <summary>
/// �u���[���B
/// </summary>
#pragma once

class PostEffect;
class Bloom
{
public:
	Bloom();
	~Bloom();

	/// <summary>
	/// �P�x���o�p�����_�[�^�[�Q�b�g�̏������B
	/// </summary>
	void InitRenderTarget();

	/// <summary>
	/// �`�揈���B
	/// </summary>
	/// <param name="postEffect">�|�X�g�G�t�F�N�g</param>
	void Draw(PostEffect& postEffect);

private:

	ID3D11SamplerState* m_samplerState = nullptr;		//�T���v���X�e�[�g�B
	ID3D11BlendState* m_disableBlendState = nullptr;	//�A���t�@�u�����f�B���O�𖳌��ɂ���u�����f�B���O�X�e�[�g�B

	Shader m_vs;						//�������Ȃ����_�V�F�[�_�[�B
	Shader m_psLuminance;				//�P�x���o�p�̃s�N�Z���V�F�[�_�[�B

	RenderTarget m_luminanceRT;			//�P�x�𒊏o���郌���_�����O�^�[�Q�b�g�B
		
};

