#pragma once
#include "Bloom.h"

class PostEffect
{
public:
	PostEffect();
	~PostEffect();

	/// <summary>
	/// �X�V�����B
	/// </summary>
	void Update();

	/// <summary>
	/// �������B
	/// </summary>
	void Init();

	/// <summary>
	/// �`�揈���B
	/// </summary>
	void Draw();

	/// <summary>
	/// �t���X�N���[���`��B
	/// </summary>
	/// <param name="deviceContext">�f�o�C�X�R���e�L�X�g</param>
	/// <param name="vsShader">���_�V�F�[�_�[</param>
	/// <param name="psShader">�s�N�Z���V�F�[�_�[</param>
	void DrawFullScreenQuadPrimitive(ID3D11DeviceContext* deviceContext, Shader& vsShader, Shader& psShader);



private:

	/// <summary>
	/// �t���X�N���[���`��p�̎l�p�`�v���~�e�B�u�̏������B
	/// </summary>
	void InitFullScreenQuadPrimitive();

	Bloom	m_bloom;	//�u���[���B
	//�t���X�N���[���`��p�̃����o�ϐ��B
	ID3D11Buffer*	m_vertexBuffer = nullptr;		//���_�o�b�t�@�B
	ID3D11InputLayout* m_inputLayout = nullptr;		//���̓��C�A�E�g�B

};

