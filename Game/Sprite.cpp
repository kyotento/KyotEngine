#include "stdafx.h"
#include "Sprite.h"

/// <summary>
/// 2D��`�悷�邽�߂̃N���X
/// </summary>
/// <remarks>
/// ���_�o�b�t�@�̃f�[�^�`�����`����\���̂�錾�B
/// �쐬���钸�_�o�b�t�@���uD3D11_BUFFER_DESC�v�Œ�`�B
/// �T�u���\�[�X�̏������f�[�^���uD3D11_SUBRESOURCE_DATA�@�\���́v�Œ�`�B
///�uID3D11Device::CreateBuffer�@���\�b�h�v�Œ��_�o�b�t�@���쐬�B
/// </remarks>

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

	//�摜�̃n�[�t�T�C�Y�B
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
void Sprite::InitSamplerState()
{

	D3D11_SAMPLER_DESC DSD;
	DSD.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;			//U�������b�v�B
	DSD.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;			//V�������b�v�B
	DSD.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;			//W�������b�v�B
	DSD.MaxAnisotropy = 1;
	DSD.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;		//�e�N�X�`���t�@�C���B

	//�T���v���[�X�e�[�g�̍쐬�B
	g_graphicsEngine->GetD3DDevice()->CreateSamplerState(&DSD, &m_samplerState);

}

//�萔�o�b�t�@�Bcpp������V�F�[�_�ɓn�������\���̂ɂ������́B
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

//�u�����h�X�e�[�g�B
void Sprite::BlendState()
{
	//�u�����h�X�e�[�g�I�u�W�F�N�g�̍쐬�B
	D3D11_BLEND_DESC blendDesc;

	blendDesc.AlphaToCoverageEnable = true;		//�`��^�[�Q�b�g�Ƀs�N�Z���l��ݒ肷��Ƃ��Ƀ��l���g�p���邩�B

	ID3D11Device* pd3d = g_graphicsEngine->GetD3DDevice();
	blendDesc.RenderTarget[0].BlendEnable = true;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_RED | D3D11_COLOR_WRITE_ENABLE_BLUE | D3D11_COLOR_WRITE_ENABLE_GREEN;
	pd3d->CreateBlendState(&blendDesc, &pBlendState);
	{
		{
			{
				D3D11_DEPTH_STENCIL_DESC desc;
				ZeroMemory(&desc, sizeof(desc));
				ID3D11Device* pd3d = g_graphicsEngine->GetD3DDevice();
				desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
				desc.DepthFunc = D3D11_COMPARISON_LESS;
				desc.DepthEnable = true;
				desc.StencilEnable = false;
				pd3d->CreateDepthStencilState(&desc, &zspriteRender);
			}
			{
				D3D11_DEPTH_STENCIL_DESC desc;
				ZeroMemory(&desc, sizeof(desc));
				ID3D11Device* pd3d = g_graphicsEngine->GetD3DDevice();
				desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
				desc.DepthFunc = D3D11_COMPARISON_LESS;
				desc.DepthEnable = false;
				desc.StencilEnable = false;
				pd3d->CreateDepthStencilState(&desc, &spriteRender);
			}
		}
		{
			D3D11_RASTERIZER_DESC desc = {};
			ID3D11Device* pd3d = g_graphicsEngine->GetD3DDevice();
			desc.CullMode = D3D11_CULL_FRONT;
			desc.FillMode = D3D11_FILL_SOLID;
			desc.DepthClipEnable = true;
			desc.MultisampleEnable = true;
			pd3d->CreateRasterizerState(&desc, &rspriteRender);
		}
	}
}

//Init�֐��B�V�F�[�_�[���[�h�p�B
void Sprite::Init(ID3D11ShaderResourceView* srv, float w, float h)
{
	m_size.x = w;
	m_size.y = h;
	//���_�o�b�t�@�̏������B
	InitVertexBuffer(w, h);
	//�C���f�b�N�X�o�b�t�@�̏������B
	InitIndexBuffer();
	//�T���v���X�e�[�g�̏������B
	InitSamplerState();

	//���_�V�F�[�_�[�����[�h�B
	/*
		�������̓��[�h����V�F�[�_�[�\�[�X�t�@�C���̃t�@�C���p�X�B
		�������̓G���g���[�|�C���g�ƂȂ�֐��̖��O�B 
		��O�����̓��[�h�����V�F�[�_�[�̃^�C�v�B
	*/
	m_vsShader.Load(
		"Assets/shader/sprite.fx",
		"VS",
		Shader::EnType::VS	//���_�V�F�[�_�[�B
	);
	//�s�N�Z���V�F�[�_�[�����[�h�B
	m_psShader.Load(
		"Assets/shader/sprite.fx",
		"PS",
		Shader::EnType::PS	//�s�N�Z���V�F�[�_�[�B
	);

	//�萔�o�b�t�@���������B
	InitConstantBuffer();


	m_texture = srv;
	if (m_texture != nullptr) {
		//m_texture->AddRef();
	}

}

//Init�֐��B�e�N�X�`�����[�h�B
void Sprite::Init(const wchar_t* TextureFilePath, float w, float h)
{
	//�摜�T�C�Y�B
	m_size.x = w;
	m_size.y = h;

	//���_�o�b�t�@�̏������B
	InitVertexBuffer(w, h);
	//�C���f�b�N�X�o�b�t�@�̏������B
	InitIndexBuffer();
	//�T���v���X�e�[�g�̏������B
	InitSamplerState();

	//�t�@�C�������g���āA�e�N�X�`�������[�h���āAShaderResrouceView���쐬����B
	HRESULT hr = DirectX::CreateDDSTextureFromFileEx(
		g_graphicsEngine->GetD3DDevice(),	//D3D�f�o�C�X
		L"Assets/modelData/utc_all2.dds",	//�ǂݍ��ރe�N�X�`���̃t�@�C���p�X�B
		0,				                    //�e�N�X�`���̍ő�T�C�Y�B0���ƃe�N�X�`���T�C�Y�����̂܂ܓǂݍ��܂��
		D3D11_USAGE_DEFAULT,		    	//���\�[�X�̎g�p�p�r�B
		D3D11_BIND_SHADER_RESOURCE,	        //���\�[�X�̃o�C���h���@�B
		0,									//0�ł悢�B
		0,									//0�ł悢�B
		false,								//false�ł����B
		nullptr,							//nullptr�ł����B
		&m_texture					        //SRV
	);

	//�萔�o�b�t�@���������B
	InitConstantBuffer();

	//�u�����h�X�e�[�g�B
	BlendState();

}

//�`�揈���B
void Sprite::Draw()
{		
	//�f�o�C�X�R���e�L�X�g���擾�B
	auto deviceContext = g_graphicsEngine->GetD3DDeviceContext();
	//�f�o�C�X�R���e�L�X�g�ɕ`��R�}���h��ςށB
	//���_�o�b�t�@��ݒ�B
	unsigned int stride = sizeof(SVertex);	//���_�o�b�t�@�̃X�g���C�h
	unsigned int offset = 0;						//���_�o�b�t�@�̃I�t�Z�b�g�B
	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);
	//�v���~�e�B�u�̃g�|���W�[��ݒ�B
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	//���_�V�F�[�_�[��ݒ�B
	deviceContext->VSSetShader(
		(ID3D11VertexShader*)m_vsShader.GetBody(),	//���_�V�F�[�_�[�B
		NULL,										//NULL�ł����B
		0											//0
	);
	//�s�N�Z���V�F�[�_�[��ݒ�B
	deviceContext->PSSetShader(
		(ID3D11PixelShader*)m_psShader.GetBody(),	//�s�N�Z���V�F�[�_�[�B
		NULL,										//NULL�ł����B
		0											//0
	);
	//���_���C�A�E�g��ݒ�B
	deviceContext->IASetInputLayout(m_vsShader.GetInputLayout());

	//�����܂Őݒ肵�����e�Ńh���[
	deviceContext->Draw(
		3,	//���_���B
		0	//�`��J�n�̒��_�ԍ��B
	);


}