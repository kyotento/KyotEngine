#include "stdafx.h"
#include "Sprite.h"

/*
���_�o�b�t�@�̃f�[�^�`�����`����\���̂�錾�B
�쐬���钸�_�o�b�t�@���uD3D11_BUFFER_DESC�v�Œ�`�B
�T�u���\�[�X�̏������f�[�^���uD3D11_SUBRESOURCE_DATA�@�\���́v�Œ�`�B
�uID3D11Device::CreateBuffer�@���\�b�h�v�Œ��_�o�b�t�@���쐬�B
*/

Sprite::Sprite()
{
}


Sprite::~Sprite()
{

}

//�X�V�֐��B
void Sprite::Update(const CVector3& trans, const CQuaternion& rot, const CVector3& scale, CVector2 pivot)
{
	//���[�J���s�{�b�g�B
	CVector2 localPivot = pivot;
	localPivot.x -= 0.5f;
	localPivot.y -= 0.5f;
	localPivot.x *= -2.0f;
	localPivot.y *= -2.0f;

	//�摜�̃T�C�Y�B
	CVector2 halfSize = m_size;
	halfSize.x *= 0.5f;
	halfSize.y *= 0.5f;

	CMatrix mPivotTrans;                        //���s�ړ��s��B
	mPivotTrans.MakeTranslation(                //�s�{�b�g��Size���g���ĕ��s�ړ��s��̌v�Z�B
		{ halfSize.x * localPivot.x, halfSize.y * localPivot.y, 0.0f }
	);

	CMatrix mTrans, mRot, mScale;
	mTrans.MakeTranslation(trans);				//���s�ړ��s��B
	mRot.MakeRotationFromQuaternion(rot);		//��]�s��B
	mScale.MakeScaling(scale);					//�g��s��B
	m_world.Mul(mPivotTrans, mScale);           //�s��̏�Z�B
	m_world.Mul(m_world, mRot);
	m_world.Mul(m_world, mTrans);
	
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
	DBD.ByteWidth = sizeof(vertex);             //���_�o�b�t�@�̃T�C�Y�B(��ō�������)�B
	DBD.Usage = D3D11_USAGE_DEFAULT;            //�ǂݏ������@�B�f�t�H���g�ŁB
	DBD.CPUAccessFlags = 0;                     //���̂܂��CPU�A�N�Z�X�t���O�B�A�N�Z�X�s�v�̏ꍇ�͂O�B
	DBD.MiscFlags = 0;                          //���̑��t���O�B���g�p�͂O�B
	DBD.StructureByteStride = 0;                //�o�b�t�@���\�����o�b�t�@��\���ꍇ�́A�o�b�t�@�\�����̊e�v�f�̃T�C�Y�i�o�C�g�P�ʁj�B
	DBD.BindFlags = D3D11_BIND_VERTEX_BUFFER;	//���ꂩ��쐬����o�b�t�@�����_�o�b�t�@�ł��邱�Ƃ��w�肷��B

	//D3D11_SUBRESOURCE_DATA �ݒ�J�n�B
	D3D11_SUBRESOURCE_DATA DSD;
	DSD.pSysMem = vertex;                       //�o�b�t�@�A�f�[�^�̏����l�B
	DSD.SysMemPitch = 0;                        //�������̃s�b�`�i�o�C�g���j�B
	DSD.SysMemSlicePitch = 0;                   //�[�x���x���i�o�C�g���j�B

	//���_�o�b�t�@�̍쐬�B
	g_graphicsEngine->GetD3DDevice()->CreateBuffer(&DBD, &DSD, &m_vertexBuffer);
}

//�C���f�b�N�X�o�b�t�@�̏������B
void Sprite::InitIndexBuffer()
{
	//���_�ԍ��B
	int index[6] = {
	0,1,2,		//�O�p�`���
	2,1,3		//�O�p�`���
	};


	//���_�o�b�t�@���l�A�C���f�b�N�X�o�b�t�@���쐬���邽�߂ɂ�D3D11_BUFFER_DESC��D3D11_SUBRESOURCE_DATA��ݒ肷��K�v������B

	//D3D11_BUFFER_DESC�ݒ�B
	D3D11_BUFFER_DESC IDBD;
	IDBD.Usage = D3D11_USAGE_DEFAULT;               //�o�b�t�@�̓ǂݍ��݁idefault�j�B
	IDBD.ByteWidth = sizeof(index);                 //�o�b�t�@�̃T�C�Y�B���_�ԍ����B
	IDBD.BindFlags = D3D11_BIND_INDEX_BUFFER;       //�C���f�b�N�X�o�b�t�@�B
	IDBD.CPUAccessFlags = 0;                        //CPU�A�N�Z�X�t���O�B
	IDBD.MiscFlags = 0;                             //���̑��t���O�B
	IDBD.StructureByteStride = 0;                   //�\�����o�b�t�@�̏ꍇ�A���̍\���̂̃T�C�Y�i�o�C�g���j�B

	//D3D11_SUBRESOURCE_DATA�ݒ�J�n�B
	D3D11_SUBRESOURCE_DATA IDSD;
	IDSD.pSysMem = index;                           //�o�b�t�@�A�f�[�^�̏����l�B
	IDSD.SysMemPitch = 0;                           //�������̃s�b�`�B
	IDSD.SysMemSlicePitch = 0;                      //�[�x���x���B

	//�C���f�b�N�X�o�b�t�@�̍쐬�B
	g_graphicsEngine->GetD3DDevice()->CreateBuffer(&IDBD, &IDSD, &m_indexBuffer);

} 

//�T���v���[�X�e�[�g�̏������B(�ǂ̂悤�Ƀe�N�X�`�����T���v������邩���`)�B
void Sprite::InitSampleState()
{

	D3D11_SAMPLER_DESC DSD;
	DSD.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	DSD.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	DSD.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	DSD.MaxAnisotropy = 1;
	DSD.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;

	//�T���v���[�X�e�[�g�̍쐬�B
	g_graphicsEngine->GetD3DDevice()->CreateSamplerState(&DSD, &m_samplerState);

}

//cpp������V�F�[�_�ɓn�������\���̂ɂ������́B
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