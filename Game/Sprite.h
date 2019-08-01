#pragma once

#include "Effect.h"
class Sprite
{
public:

	Sprite();
	~Sprite();

	static const CVector2 Default_Pivot;		//�f�t�H���g�̃s�{�b�g�B

	//���_�o�b�t�@�̍��W�B
	struct SVertex {
		float position[4];
		float uv[2];
	};

	//�萔�o�b�t�@�B
	struct ConstantBuffer {
		CMatrix WVP;
		CVector4 mulCol;
	};

	void Init(ID3D11ShaderResourceView* srv, float w, float h);

	//�������B
	/*
		TextureFilePath = �e�N�X�`���̃t�@�C���p�X�B
		w               = ��m�̕��B
		h               = ��m�̍����B
	*/
	void Init(const wchar_t* TextureFilePath, float w, float h);


	//�`��̍X�V�����B
	/*
		trans = ���s�ړ��B
		rot   = ��]�B
		scale = �g��B
		pivot = ��_�B { 0 , 0 }     �摜�̍���B
		               { 0.5 , 0.5 } ��ʂ̒��S�B 
					   { 1 , 1 }     ��ʂ̉E���B
	*/
	void Update(const CVector3& trans, const CQuaternion& rot, const CVector3& scale, CVector2 pivot = { 0.5f, 0.5f });

	void Draw();

	//�萔�o�b�t�@�̏������B
	void InitConstantBuffer();

	CVector2 m_size = CVector2::Zero();            //�摜�̃T�C�Y�B

	CMatrix	m_world = CMatrix::Identity();			//���[���h�s��B

	ID3D11Buffer* m_vertexBuffer = NULL;           //���_�o�b�t�@�B
	ID3D11Buffer* m_indexBuffer = NULL;            //�C���f�b�N�X�o�b�t�@�B
	Effect m_effect;                               //�G�t�F�N�g�B
	ID3D11RenderTargetView* m_texture = NULL;      //�e�N�X�`���B
	ID3D11SamplerState* m_samplerState = NULL;     //�T���v���[�X�e�[�g�B


	//���_�o�b�t�@�̏������B
	void InitVertexBuffer(float w, float h);

	//�C���f�b�N�X�o�b�t�@�̏������B
	void InitIndexBuffer();

	//�T���v���X�e�[�g�̏������B
	void InitSampleState();

};

