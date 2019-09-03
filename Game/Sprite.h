#pragma once

#include "Effect.h"
#include "graphics/Shader.h"
#include "graphics/Camera.h"
class Sprite
{
public:

	Sprite();
	~Sprite();

	/// <summary>
	/// default��Povot�B
	/// </summary>
	static const CVector2	DEFAULT_PIVOT;					//!<�s�{�b�g�B


	/// <summary>
	/// ���_�o�b�t�@�̍��W
	/// </summary>
	struct SVertex {
		float position[4];
		float uv[2];
	};

	/// <summary>
	/// �萔�o�b�t�@
	/// </summary>
	struct ConstantBuffer {
		CMatrix WVP;
		CVector4 mulCol;
	};

	/// <summary>
	/// �V�F�[�_�[���[�h
	/// </summary>
	/// <param name="srv">�����_�����O���ɃV�F�[�_�[���A�N�Z�X�ł���T�u���\�[�X���w��</param>
	/// <param name="w">�摜�̕�</param>
	/// <param name="h">�摜�̍���</param>
	void Init(ID3D11ShaderResourceView* srv, float w, float h);

	/// <summary>
	/// �e�N�X�`�����[�h�������B
	/// </summary>
	/// <param name="TextureFilePath">�e�N�X�`���̃t�@�C���p�X</param>
	/// <param name="w">�摜�̕�</param>
	/// <param name="h">�摜�̍���</param>
	void Init(const wchar_t* TextureFilePath, float w, float h);

	/// <summary>
	/// �`��̍X�V�����B
	/// </summary>
	/// <param name="trans">���s�ړ�</param>
	/// <param name="rot">��]</param>
	/// <param name="scale">�g��</param>
	/// <param name="pivot">��_</param>
	///                    { 0 , 0 }     �摜�̍���B
	///					   { 0.5, 0.5 } ��ʂ̒��S�B
	///					   { 1 , 1 }     ��ʂ̉E���B
	void Update(const CVector3& trans, const CQuaternion& rot, const CVector3& scale, CVector2 pivot = { 0.5f, 0.5f });

	/// <summary>
	/// �`�揈���B
	/// </summary>
	void Draw();

	/// <summary>
	/// �u�����h�̏������B
	/// </summary>
	void BlendState();

	/// <summary>
	/// �萔�o�b�t�@�̏������B
	/// </summary>
	void InitConstantBuffer();

	CVector2 m_size = CVector2::Zero();						//�摜�̃T�C�Y�B

	CMatrix	m_world = CMatrix::Identity();					//���[���h�s��B

	Camera::EnUpdateProjMatrixFunc m_cameraMode = Camera::enUpdateProjMatrixFunc_Ortho;

	ID3D11Buffer* m_vertexBuffer = NULL;					  //���_�o�b�t�@�B
	ID3D11Buffer* m_indexBuffer = NULL;						  //�C���f�b�N�X�o�b�t�@�B
	ID3D11DepthStencilState* m_depthStencilState = NULL;
	ID3D11DepthStencilState*	spriteRender = NULL;
	ID3D11DepthStencilState*	zspriteRender = NULL;
	ID3D11BlendState* pBlendState = NULL;					//�u�����h�X�e�[�g�B
	ID3D11RasterizerState*	rspriteRender = NULL;
	ID3D11Buffer*				m__cb = nullptr;							//�萔�o�b�t�@�B

	ID3D11ShaderResourceView* m_texture = NULL;				//�e�N�X�`���B
	ID3D11SamplerState* m_samplerState = NULL;				 //�T���v���[�X�e�[�g�B
	Effect m_effect;										 //�G�t�F�N�g�B
	Shader m_vsShader;										 //���_�V�F�[�_�[�B
	Shader m_psShader;										 //�s�N�Z���V�F�[�_�[�B

	CVector4					m_mulCol = { 1.f,1.f,1.f,1.f };
	/// <summary>
	/// ���_�o�b�t�@�̏�����
	/// </summary>
	/// <param name="w">�摜�̕�</param>
	/// <param name="h">�摜�̍���</param>
	void InitVertexBuffer(float w, float h);

	/// <summary>
	/// �C���f�b�N�X�o�b�t�@�̏�����
	/// </summary>
	void InitIndexBuffer();

	/// <summary>
	/// �T���v���X�e�[�g�̏�����
	/// </summary>
	void InitSamplerState();

};
