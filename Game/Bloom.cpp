#include "stdafx.h"
#include "Bloom.h"
#include "PostEffect.h"

Bloom::Bloom()
{

}


Bloom::~Bloom()
{
	if (m_disableBlendState != nullptr) {
		m_disableBlendState->Release();
	}

	if (m_samplerState != nullptr) {
		m_samplerState->Release();
	}
	if (m_finalBlendState != nullptr) {
		m_finalBlendState->Release();
	}
}

void Bloom::Init()
{
	//�����_�[�^�[�Q�b�g�̏������B
	InitRenderTarget();

	//�V�F�[�_�[�̏������B
	InitShader();

	//���u�����f�B���O�X�e�[�g�̏������B
	InitAlphaBlendState();

	//�T���v���[�X�e�[�g�̏������B
	InitSamplerState();

	//�K�E�V�A���u���[�̏������B
	ID3D11ShaderResourceView* srcBlirTexture = m_luminanceRT.GetRenderTargetSRV();
	for (auto& gaussianBlur : m_gausianBlur) {
		gaussianBlur.Init(srcBlirTexture, 25.f);
		//���̃K�E�V�A���u���[�Ŏg�p����\�[�X�e�N�X�`����ݒ肷��B
		srcBlirTexture = gaussianBlur.GetResultTextureSRV();
	}
}

//�����_�����O�^�[�Q�b�g�̏������B
void Bloom::InitRenderTarget()
{
	//�P�x���o�p�̃����_�����O�^�[�Q�b�g���쐬����B
	m_luminanceRT.Create(
		FRAME_BUFFER_W,
		FRAME_BUFFER_H,
		DXGI_FORMAT_R16G16B16A16_FLOAT
	);

	//�t���[���o�b�t�@��1/2�̉𑜓x�̃{�P�摜�����p�̃����_�����O�^�[�Q�b�g���쐬����B
	//��ԉ𑜓x���������̂�1/2�̂��߂��̉𑜓x�B
	m_blurCombineRT.Create(
		FRAME_BUFFER_W / 2,
		FRAME_BUFFER_H / 2,
		DXGI_FORMAT_R16G16B16A16_FLOAT
	);
}

//�V�F�[�_�[�̏������B
void Bloom::InitShader()
{
	m_vs.Load("Assets/shader/bloom.fx", "VSMain", Shader::EnType::VS);
	m_psLuminance.Load("Assets/shader/bloom.fx", "PSSamplingLuminance", Shader::EnType::PS);
	m_psFinal.Load("Assets/shader/bloom.fx", "PSFinal", Shader::EnType::PS);

	//�{�P�摜�����p�̃s�N�Z���V�F�[�_�[�����[�h����B
	m_psCombine.Load("Assets/shader/bloom.fx", "PSCombine", Shader::EnType::PS);
}

//���u�����f�B���O�X�e�[�g�̏������B
void Bloom::InitAlphaBlendState()
{
	CD3D11_DEFAULT defaultSettings;
	//�f�t�H���g�Z�b�e�B���O�ŏ���������B
	CD3D11_BLEND_DESC blendDesc(defaultSettings);
	auto device = g_graphicsEngine->GetD3DDevice();

	//�u�����h�X�e�[�g�̍쐬�B
	device->CreateBlendState(&blendDesc, &m_disableBlendState);

	//�ŏI�����p�̃u�����h�X�e�[�g���쐬����B
	//�ŏI�����͉��Z�����B
	blendDesc.RenderTarget[0].BlendEnable = true;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	device->CreateBlendState(&blendDesc, &m_finalBlendState);
}

//�T���v���[�X�e�[�g�̏������B
void Bloom::InitSamplerState()
{
	D3D11_SAMPLER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	g_graphicsEngine->GetD3DDevice()->CreateSamplerState(&desc, &m_samplerState);
}

//�`�揈���B
void Bloom::Draw(PostEffect& postEffect)
{
	//�f�o�C�X�R���e�L�X�g�̏������B
	auto deviceContext = g_graphicsEngine->GetD3DDeviceContext();
	deviceContext->PSSetSamplers(0, 1, &m_samplerState);

	//���u�����h�𖳌��ɂ���B
	float blendFactor[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	deviceContext->OMSetBlendState(m_disableBlendState, blendFactor, 0xffffffff);

	//�����_�����O�^�[�Q�b�g�̃N���A�B
	float clearColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	m_luminanceRT.ClearRenderTarget(clearColor);

	//�P�x���o�p�̃����_�����O�^�[�Q�b�g�ɕύX�B
	g_graphicsEngine->ChangeRenderTarget(&m_luminanceRT, m_luminanceRT.GetViewport());


	//�V�[�����e�N�X�`���Ƃ���B
	auto mainRTTexSRV = IGameObjectManager().GetMainRenderTarget()->GetRenderTargetSRV();
	deviceContext->PSSetShaderResources(0, 1, &mainRTTexSRV);

	//�t���X�N���[���`��B
	postEffect.DrawFullScreenQuadPrimitive(deviceContext, m_vs, m_psLuminance);

	//�P�x�e�N�X�`�����K�E�V�A���u���[�łڂ����B
	for (auto& GaussianBlur : m_gausianBlur) {
		GaussianBlur.Execute(postEffect);
	}

	///<remarks>
	/// �K�E�V�A���u���[�łڂ������摜��1/2�̉𑜓x�̃����_�����O�^�[�Q�b�g�Ɏg�p���č�������B
	/// </remarks>
	//�����_�����O�^�[�Q�b�g���ڂ����摜�����p�̃��m�ɂ���B
	g_graphicsEngine->ChangeRenderTarget(&m_blurCombineRT, m_blurCombineRT.GetViewport());
	//�K�E�V�A���u���[���������e�N�X�`����t0�`t3���W�X�^�ɐݒ肷��B
	for (int registerNo = 0; registerNo < NUM_DOWN_SAMPLE; registerNo++) {
		auto srv = m_gausianBlur[registerNo].GetResultTextureSRV();
		deviceContext->PSSetShaderResources(registerNo, 1, &srv);
	}

	//�t���X�N���[���`��B
	postEffect.DrawFullScreenQuadPrimitive(deviceContext, m_vs, m_psCombine);

	/// <remarks>
	/// �ڂ������G�����Z�����Ń��C�������_�����O�^�[�Q�b�g�ɍ����B
	/// </remarks>
	auto mainRT = IGameObjectManager().GetMainRenderTarget();
	g_graphicsEngine->ChangeRenderTarget(mainRT, mainRT->GetViewport());

	//���������{�P�e�N�X�`���̃A�h���X��t0���W�X�^�ɐݒ肷��B
	auto srv = m_blurCombineRT.GetRenderTargetSRV();
	deviceContext->PSSetShaderResources(0, 1, &srv);

	//���Z�����p�̃u�����f�B���O�X�e�[�g��ݒ肷��B
	deviceContext->OMSetBlendState(m_finalBlendState, blendFactor, 0xffffffff);
	//�t���X�N���[���`��B
	postEffect.DrawFullScreenQuadPrimitive(deviceContext, m_vs, m_psFinal);

	//�u�����f�B���O�X�e�[�g��߂��B
	deviceContext->OMSetBlendState(m_disableBlendState, blendFactor, 0xffffffff);
}