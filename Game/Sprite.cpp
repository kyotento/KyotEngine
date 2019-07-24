#include "stdafx.h"
#include "Sprite.h"


Sprite::Sprite()
{
}


Sprite::~Sprite()
{

}

//���_�o�b�t�@�̏������B
void Sprite::InitVertexBuffer(float w, float h)
{

	//���W�̐ݒ�B

	float halfW = w * 0.5f;
	float halfH = h * 0.5f;
	SVertex vertex[4] = {
		//���_�P
		{
			//���W�@position[4]
			-halfW,  -halfH, 0.0f, 1.0f,
			//UV���W uv[2]
			0.0f, 1.0f
		},
		//���_�Q
		{
			//���W�@position[4]
			halfW, -halfH, 0.0f, 1.0f,
			//UV���W uv[2]
			1.0f, 1.0f
		},
		//���_�R
		{
			//���W�@position[4]
			-halfW,  halfH, 0.0f, 1.0f,
			//UV���W uv[2]
			0.0f, 0.0f
		},
		//���_�S
		{
			//���W�@position[4]
			halfW,  halfH, 0.0f, 1.0f,
			//UV���W uv[2]
			1.0f, 0.0f
		},
	};

	//���Œ�`�������_���g���B
	//���_�o�b�t�@���쐬���邽�߂ɂ�D3D11_BUFFER_DESC��D3D11_SUBRESOURCE_DATA��ݒ肷��K�v������B

	//D3D11_BUFFER_DESC �ݒ�J�n�B
	D3D11_BUFFER_DESC DBD;
	DBD.ByteWidth = sizeof(vertex);       //���_�o�b�t�@�̃T�C�Y�B(��ō�������)�B
	DBD.Usage = D3D11_USAGE_DEFAULT;      //�ǂݏ������@�B�f�t�H���g�ŁB
	DBD.CPUAccessFlags = 0;               //���̂܂��CPU�A�N�Z�X�t���O�B�A�N�Z�X�s�v�̏ꍇ�͂O�B
	DBD.MiscFlags = 0;                    //���̑��t���O�B���g�p�͂O�B
	DBD.StructureByteStride = 0;          //�o�b�t�@���\�����o�b�t�@��\���ꍇ�́A�o�b�t�@�\�����̊e�v�f�̃T�C�Y�i�o�C�g�P�ʁj�B

	
}

//�C���f�b�N�X�o�b�t�@�̏������B
void Sprite::InitIndexBuffer()
{
	//���_�ԍ��B
	int index[6] = {
	0,1,2,		//�O�p�`���
	2,1,3		//�O�p�`���
	};

}

//�T���v���X�e�[�g�̏������B
void Sprite::InitSampleState()
{

}

//
void Sprite::InitConstantBuffer()
{
	D3D11_BUFFER_DESC desc;
	// ���_�o�b�t�@�̏������ݒ�
	desc.ByteWidth = (((sizeof(ConstantBuffer) - 1) / 16) + 1) * 16;  //�o�b�t�@�̃T�C�Y�B
	desc.Usage = D3D11_USAGE_DEFAULT;                                 //�o�b�t�@�̓ǂݏ������@�B
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;                      //�o�b�t�@���p�C�v���C���ɂǂ̂悤�Ƀo�C���h���邩���w��B
	desc.CPUAccessFlags = 0;                                          //���̂܂��CPU�A�N�Z�X�t���O�B�A�N�Z�X�s�v�̏ꍇ�͂O�B
	desc.MiscFlags = 0;                                               //���̑��t���O�B���g�p�͂O�B
	desc.StructureByteStride = 0;                                     //�o�b�t�@���\�����o�b�t�@��\���ꍇ�́A�o�b�t�@�\�����̊e�v�f�̃T�C�Y�i�o�C�g�P�ʁj�B
}

//Init�֐��B
void Sprite::Init(const wchar_t* TextureFilePath, float w, float h)
{
	//���_�o�b�t�@�̏������B
	InitVertexBuffer(w,h);
	//�C���f�b�N�X�o�b�t�@�̏������B
	InitIndexBuffer();
	//�T���v���X�e�[�g�̏������B
	InitSampleState();
	//�G�t�F�N�g�t�@�C���̃��[�h�B
	//m_effect.Load("Assets/shader/");


}