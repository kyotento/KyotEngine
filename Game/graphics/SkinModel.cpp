#include "stdafx.h"
#include "SkinModel.h"
#include "SkinModelDataManager.h"
#include "SkinModelEffect.h"

SkinModel::~SkinModel()
{
	if (m_cb != nullptr) {
		//�萔�o�b�t�@������B
		m_cb->Release();
	}
	if (m_samplerState != nullptr) {
		//�T���v���X�e�[�g������B
		m_samplerState->Release();
	}

	//���C�g�p�萔�o�b�t�@�̊J���B
	if (m_lightConstantBuffer != nullptr)
	{
		m_lightConstantBuffer->Release();
	}

}
void SkinModel::Init(const wchar_t* filePath,/* EnFbxUpAxis enFbxUpAxis,*/ const char* entryPS, const char* entryVS/*, bool ShadowReciever = true*/)
{
	m_psmain = entryPS;
	m_vsmain = entryVS;

	//�X�P���g���̃f�[�^��ǂݍ��ށB
	InitSkeleton(filePath);

	//�萔�o�b�t�@�̍쐬�B
	InitConstantBuffer();

	//�T���v���X�e�[�g�̏������B
	InitSamplerState();

	//�f�B���N�V�������C�g�̏������B
	InitDirectionLight();

	//SkinModelDataManager���g�p����CMO�t�@�C���̃��[�h�B
	m_modelDx = g_skinModelDataManager.Load(filePath, m_skeleton);

	//�e�𐶐����邩�ۂ��B
	/*SetShadowReciever(ShadowReciever);*/

	//m_enFbxUpAxis = enFbxUpAxis;
}
void SkinModel::InitSkeleton(const wchar_t* filePath)
{
	//�X�P���g���̃f�[�^��ǂݍ��ށB
	//cmo�t�@�C���̊g���q��tks�ɕύX����B
	std::wstring skeletonFilePath = filePath;
	//�����񂩂�.cmo�t�@�C���n�܂�ꏊ�������B
	int pos = (int)skeletonFilePath.find(L".cmo");
	//.cmo�t�@�C����.tks�ɒu��������B
	skeletonFilePath.replace(pos, 4, L".tks");
	//tks�t�@�C�������[�h����B
	//�������ŗ������l�ցB�t�@�C���p�X�Ԉ���ĂȂ��H�B
	bool result = m_skeleton.Load(skeletonFilePath.c_str());
	if ( result == false ) {
		//�X�P���g�����ǂݍ��݂Ɏ��s�����B
		//�A�j���[�V�������Ȃ����f���́A�X�P���g�����s�v�Ȃ̂�
		//�ǂݍ��݂Ɏ��s���邱�Ƃ͂���̂ŁA���O�o�͂����ɂ��Ă����B
#ifdef _DEBUG
		char message[256];
		sprintf(message, "tks�t�@�C���̓ǂݍ��݂Ɏ��s���܂����B%ls\n", skeletonFilePath.c_str());
		OutputDebugStringA(message);
#endif
	}
}
void SkinModel::InitConstantBuffer()
{
	//�쐬����o�b�t�@�̃T�C�Y��sizeof���Z�q�ŋ��߂�B
	int bufferSize = sizeof(SVSConstantBuffer);
	//�ǂ�ȃo�b�t�@���쐬����̂�������bufferDesc�ɐݒ肷��B
	D3D11_BUFFER_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(bufferDesc));				//�O�ŃN���A�B
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;						//�o�b�t�@�őz�肳��Ă���A�ǂݍ��݂���я������ݕ��@�B
	bufferDesc.ByteWidth = (((bufferSize - 1) / 16) + 1) * 16;	//�o�b�t�@��16�o�C�g�A���C�����g�ɂȂ��Ă���K�v������B
																//�A���C�����g���ā��o�b�t�@�̃T�C�Y��16�̔{���Ƃ������Ƃł��B
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;			//�o�b�t�@���ǂ̂悤�ȃp�C�v���C���Ƀo�C���h���邩���w�肷��B
																//�萔�o�b�t�@�Ƀo�C���h����̂ŁAD3D11_BIND_CONSTANT_BUFFER���w�肷��B
	bufferDesc.CPUAccessFlags = 0;								//CPU �A�N�Z�X�̃t���O�ł��B
																//CPU�A�N�Z�X���s�v�ȏꍇ��0�B
	//�쐬�B
	g_graphicsEngine->GetD3DDevice()->CreateBuffer(&bufferDesc, NULL, &m_cb);

	//���C�g�p�̒萔�o�b�t�@���쐬�B
	//�쐬����o�b�t�@�̃T�C�Y��ύX����B
	bufferDesc.ByteWidth = sizeof(DirectionLight);				//DirectionLight��16byte�̔{���ɂȂ��Ă���̂ŁA�؂�グ�͂��Ȃ��B
	g_graphicsEngine->GetD3DDevice()->CreateBuffer(&bufferDesc, NULL, &m_lightConstantBuffer);
}
void SkinModel::InitSamplerState()
{
	//�e�N�X�`���̃T���v�����O���@���w�肷�邽�߂̃T���v���X�e�[�g���쐬�B
	D3D11_SAMPLER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	g_graphicsEngine->GetD3DDevice()->CreateSamplerState(&desc, &m_samplerState);
}

void SkinModel::InitDirectionLight()
{
	//���z��
	m_directionLight.direction[0] = { -1.0f,-1.0f,1.0f,0.0f };
	m_directionLight.direction[0].Normalize();
	m_directionLight.color[0] = { 0.4f,0.4f,0.4f,1.f };

	//�n�ʂ̏Ƃ�Ԃ�
	/*m_directionLight.direction[1] = { 1.0f,-1.0f,1.0f,0.0f };
	m_directionLight.direction[1].Normalize();
	m_directionLight.color[1] = { 0.1f,0.1f,0.1f,1.f };


	m_directionLight.direction[2] = { -1.0f,0.5f,0.0f,0.0f };
	m_directionLight.direction[2].Normalize();
	m_directionLight.color[2] = { 0.0f,0.0f,0.0f,1.f };

	m_directionLight.direction[3] = { 1.0f,0.5f,1.0f,0.0f };
	m_directionLight.direction[3].Normalize();
	m_directionLight.color[3] = { 0.0f,0.0f,0.0f,1.f };

	m_directionLight.direction[4] = { 0.f,0.f,1.0f,0.0f };
	m_directionLight.color[4] = { 0.3f,0.3f,0.3f,1.f };
	*/
	m_directionLight.specPos = 0.0f;
	m_directionLight.ambientLig = { 0.5f, 0.5f, 0.5f, 1.0f };
	/*for (int i = 0; i < directionLightNum; i++)
	{
		if (i == 0) {
			m_directionLight.direction[i] = { 0.f,0.f,-1.0f,0.0f };
			m_directionLight.color[i] = { 1.f,1.f,1.f,1.f };
		}

		if (i == 1) {
			m_directionLight.direction[i] = { 0.f,0.f,-1.0f,0.0f };
			m_directionLight.color[i] = { 1.f,1.f,1.f,1.f };
		}
	}*/
}

void SkinModel::UpdateWorldMatrix(CVector3 position, CQuaternion rotation, CVector3 scale)
{
	//3dsMax�Ǝ������킹�邽�߂̃o�C�A�X�B
	CMatrix mBias = CMatrix::Identity();
	if (m_enFbxUpAxis == enFbxUpAxisZ) {
		//Z-up
		mBias.MakeRotationX(CMath::PI * -0.5f);
	}
	CMatrix transMatrix, rotMatrix, scaleMatrix;
	//���s�ړ��s����쐬����B
	transMatrix.MakeTranslation( position );
	//��]�s����쐬����B
	rotMatrix.MakeRotationFromQuaternion( rotation );
	rotMatrix.Mul(mBias, rotMatrix);
	//�g��s����쐬����B
	scaleMatrix.MakeScaling(scale);
	//���[���h�s����쐬����B
	//�g��~��]�~���s�ړ��̏��Ԃŏ�Z����悤�ɁI
	//���Ԃ��ԈႦ���猋�ʂ��ς���B
	m_worldMatrix.Mul(scaleMatrix, rotMatrix);
	m_worldMatrix.Mul(m_worldMatrix, transMatrix);

	//�X�P���g���̍X�V�B
	m_skeleton.Update(m_worldMatrix);
}
void SkinModel::Draw(EnRenderMode renderMode, CMatrix viewMatrix, CMatrix projMatrix)
{
	DirectX::CommonStates state(g_graphicsEngine->GetD3DDevice());

	ID3D11DeviceContext* d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();

	auto shadowMap = IGameObjectManager().GetShadowMap();		//�V���h�E�}�b�v���擾�B
	//�萔�o�b�t�@�̓��e���X�V�B
	SVSConstantBuffer vsCb;
	vsCb.mWorld = m_worldMatrix;
	vsCb.mProj = projMatrix;
	vsCb.mView = viewMatrix;
	//���C�g�̃J�����r���[�A�v���W�F�N�V�����s��𑗂�B
	vsCb.mLightProj = shadowMap->GetLightProjMatrix();
	vsCb.mLightView = shadowMap->GetLighViewMatrix();
	//�V���h�E�}�b�v�𐶐����邩�ǂ��������߂�B
	if (m_isShadowReciever) {			//�t���O��true�̂Ƃ��B
		vsCb.isShadowReciever = 1;		//�e�𐶐�����B
	}
	else {								//�t���O��false�̂Ƃ��B
		vsCb.isShadowReciever = 0;		//�e�𐶐����Ȃ��B
	}
//	vsCb.ambientLight = g_graphicsEngine->GetAmbientLight();
	//���C���������̓��e��VRAM�ɃR�s�[�iVRAM�F�F�@GPU���A�N�Z�X���郁�����j�B
	d3dDeviceContext->UpdateSubresource(m_cb, 0, nullptr, &vsCb, 0, 0);
	//���_��ݒ�B
	m_directionLight.eyePos = g_camera3D.GetPosition();
	//���ʔ��ˌ��̍i���ݒ�B
	//m_directionLight.specPos = 2.f;
	
	//���C�g�p�̒萔�o�b�t�@���X�V�B
	d3dDeviceContext->UpdateSubresource(m_lightConstantBuffer, 0, nullptr, &m_directionLight, 0, 0);
	//�萔�o�b�t�@��GPU�ɓ]���B
	d3dDeviceContext->VSSetConstantBuffers(0, 1, &m_cb);
	d3dDeviceContext->PSSetConstantBuffers(0, 1, &m_cb);
	d3dDeviceContext->PSSetConstantBuffers(1, 1, &m_lightConstantBuffer);
	//�T���v���X�e�[�g��ݒ�B
	d3dDeviceContext->PSSetSamplers(0, 1, &m_samplerState);
	//�{�[���s���GPU�ɓ]���B
	m_skeleton.SendBoneMatrixArrayToGPU();
	//�V���h�E�}�b�v�����W�X�^�ɓ]���B(�����Ă�H)
	d3dDeviceContext->PSSetShaderResources(2, 1, &m_shadowMapSRV);
	//�G�t�F�N�g�ɃN�G����������B
	m_modelDx->UpdateEffects([&](DirectX::IEffect* material) {
		auto modelMaterial = reinterpret_cast<ModelEffect*>(material);
		modelMaterial->SetRenderMode(renderMode);
	});

	//�`��B
	m_modelDx->Draw(
		d3dDeviceContext,
		state,
		m_worldMatrix,
		viewMatrix,
		projMatrix
	);
}