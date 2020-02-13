#include "stdafx.h"
#include "GaussianBlur.h"
#include "PostEffect.h"

GaussianBlur::GaussianBlur()
{
}


GaussianBlur::~GaussianBlur()
{
}

//�������B
void GaussianBlur::Init(ID3D11ShaderResourceView* srcTextureSRV, float blurPow)
{
	//�\�[�X�e�N�X�`����SRV���R�s�[�B
	m_srcTextureSRV = srcTextureSRV;
	//�u���[�̋�����ێ��B
	m_blurPower = blurPow;

	//�e�N�X�`���̏����擾�B
	ID3D11Texture2D* texture;
	//SRV�̃e�N�X�`�����擾����B
	srcTextureSRV->GetResource((ID3D11Resource**)&texture);

	//�e�N�X�`�����̎擾�B
	D3D11_TEXTURE2D_DESC textureDesc;
	texture->GetDesc(&textureDesc);
	//�e�N�X�`���̏����擾��A�Q�ƃJ�E���^�������B
	texture->Release();

	m_srcTextureWidth = textureDesc.Width;			//�e�N�X�`���̕���ێ��B
	m_srcTextureHeight = textureDesc.Height;		//�e�N�X�`���̍�����ێ��B

	/// <remarks>
	/// X����Y���𕪂��ď��������ق����e�N�X�`�������ꂢ�ɂł���(�炵��)�B
	/// </remarks>	
	//X�u���[�p�̃����_�����O�^�[�Q�b�g���쐬�B(���̉𑜓x�𔼕��ɂ���)�B
	m_renderTarget[enRenderTarget_X].Create(textureDesc.Width / 2, textureDesc.Height, textureDesc.Format);
	//Y�u���[�p�̃����_�����O�^�[�Q�b�g���쐬�B(�c���̉𑜓x�𔼕��ɂ���)�B
	m_renderTarget[enRenderTarget_Y].Create(textureDesc.Width / 2, textureDesc.Height / 2, textureDesc.Format);

	//�V�F�[�_�[�����[�h�B
	m_vsXBlur.Load("Assets/shader/GaussianBlur.fx", "VSXBlur", Shader::EnType::VS);
	m_vsYBlur.Load("Assets/shader/GaussianBlur.fx", "VSYBlur", Shader::EnType::VS);
	m_psBlur.Load("Assets/shader/GaussianBlur.fx", "PSBlur", Shader::EnType::PS);

	//VRAM��ɒ萔�o�b�t�@���쐬�B(�̈�m�ۂ̂���)�B
	m_blurCbGpu.Create(nullptr, sizeof(SBlurParam));

	//�����������̂Ńt���O��Ԃ��B
	m_isInit = true;
}

//�u���[�̏d�݂��X�V�B
void GaussianBlur::UpdateWeights()
{
	//�d�݂̃g�[�^���B
	float total = 0;
	//�K�E�X�t�B���^�̏d�݂��X�V�B
	for (int i = 0; i < NUM_WEIGHTS; i++) {
		m_blurParam.weights[i] = expf(-0.5f*(float)(i*i) / m_blurPower);
		total += 2.0f*m_blurParam.weights[i];
	}

	// �K�i���B�d�݂̃g�[�^����1.0�ɂȂ�悤�ɁA�S�̂̏d�݂ŏ��Z�B
	for (int i = 0; i < NUM_WEIGHTS; i++) {
		m_blurParam.weights[i] /= total;
	}
}

void GaussianBlur::Execute(PostEffect& postEffect)
{
	//������������Ă��Ȃ��Ƃ��A�������s��Ȃ��B
	if (!m_isInit) {
		return;
	}

	auto deviceContext = g_graphicsEngine->GetD3DDeviceContext();

	//�u���[�̏d�݂��X�V�B
	UpdateWeights();

	//�d�݂̍X�V��AVRAM��̒萔�o�b�t�@���X�V�B
	//���C���������̓�����VRAM�ɃR�s�[�B
	auto d3d11CbGPU = m_blurCbGpu.GetD3D11Buffer();
	deviceContext->UpdateSubresource(d3d11CbGPU, 0, nullptr, &m_blurParam, 0, 0);
	//���W�X�^b0��m_blurCbGPU�̃A�h���X�Ɛݒ肷��B
	deviceContext->PSSetConstantBuffers(0, 1, &d3d11CbGPU);


	//X�u���[�p�̃����_�����O�^�[�Q�b�g�ɕύX����B
	g_graphicsEngine->ChangeRenderTarget(
		&m_renderTarget[enRenderTarget_X],
		m_renderTarget[enRenderTarget_X].GetViewport()
	);
	//�\�[�X�e�N�X�`���̃A�h���X��t0���W�X�^�ɐݒ肷��B
	deviceContext->VSSetShaderResources(0, 1, &m_srcTextureSRV);
	deviceContext->PSSetShaderResources(0, 1, &m_srcTextureSRV);

	//�t���X�N���[���`����s���ău���[�����s�B
	postEffect.DrawFullScreenQuadPrimitive(deviceContext, m_vsXBlur, m_psBlur);


	//Y�u���[�p�̃����_�����O�^�[�Q�b�g�ɕύX����B
	g_graphicsEngine->ChangeRenderTarget(
		&m_renderTarget[enRenderTarget_Y],
		m_renderTarget[enRenderTarget_Y].GetViewport()
	);
	//Y�u���[��������\�[�X�e�N�X�`���̃A�h���X��t0�ɐݒ肷��B
	//Y�u���[��������̂�X�u���[���������e�N�X�`���ɂȂ�B
	auto srcTextureSrv = m_renderTarget[enRenderTarget_X].GetRenderTargetSRV();
	deviceContext->VSSetShaderResources(0, 1, &srcTextureSrv);
	deviceContext->PSSetShaderResources(0, 1, &srcTextureSrv);

	//�t���X�N���[���`����s���ău���[�����s�B
	postEffect.DrawFullScreenQuadPrimitive(
		deviceContext, m_vsYBlur, m_psBlur
	);

}