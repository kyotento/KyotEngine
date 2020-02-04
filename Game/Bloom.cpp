#include "stdafx.h"
#include "Bloom.h"
#include "PostEffect.h"

Bloom::Bloom()
{
}


Bloom::~Bloom()
{
}

void Bloom::InitRenderTarget()
{
	//�P�x���o�p�̃����_�����O�^�[�Q�b�g���쐬����B
	m_luminanceRT.Create(
		FRAME_BUFFER_W,
		FRAME_BUFFER_H,
		DXGI_FORMAT_R16G16B16A16_FLOAT
	);
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

	//�P�x���o�p�̃����_�����O�^�[�Q�b�g�ɕύX�B
	g_graphicsEngine->ChangeRenderTarget(&m_luminanceRT, m_luminanceRT.GetViewport());

	//�����_�����O�^�[�Q�b�g�̃N���A�B
	float clearColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	m_luminanceRT.ClearRenderTarget(clearColor);

	//�V�[�����e�N�X�`���Ƃ���B
	auto mainRTTexSRV = IGameObjectManager().GetMainRenderTarget()->GetRenderTargetSRV();
	deviceContext->PSSetShaderResources(0, 1, &mainRTTexSRV);

	//�t���X�N���[���`��B
	postEffect.DrawFullScreenQuadPrimitive(deviceContext, m_vs, m_psLuminance);
}