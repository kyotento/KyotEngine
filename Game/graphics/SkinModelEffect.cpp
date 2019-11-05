#include "stdafx.h"
#include "graphics/SkinModelEffect.h"
#include "graphics/SkinModelShaderConst.h"

ModelEffect::ModelEffect()
{
	m_psShader.Load("Assets/shader/model.fx", "PSMain", Shader::EnType::PS);
	m_vsShader.Load("Assets/shader/model.fx", "VSMain", Shader::EnType::VS);
	m_psSilhouette.Load("Assets/shader/model.fx", "PSMain_Silhouette", Shader::EnType::PS);
	//�V���h�E�}�b�v�p�̃V�F�[�_�[�����[�h�B
	m_psShadowMap.Load("Assets/shader/model.fx", "PSMain_ShadowMap", Shader::EnType::PS);
	m_vsShadowMap.Load("Assets/shader/model.fx", "VSMain_ShadowMap", Shader::EnType::VS);

	m_pPSShader = &m_psShader;

	InitSilhouettoDepthStepsilState();
	
}

ModelEffect::~ModelEffect()
{
	
	if (m_albedoTex) {
		m_albedoTex->Release();
	}

	if (m_silhouettoDepthStepsilState != nullptr) {
		m_silhouettoDepthStepsilState->Release();
	}
	
}

void ModelEffect::InitSilhouettoDepthStepsilState()
{
	//D3D�f�o�C�X���擾�B
	auto pd3d = g_graphicsEngine->GetD3DDevice();
	//�쐬����[�x�X�e���V���X�e�[�g�̒�`��ݒ肵�Ă����B
	D3D11_DEPTH_STENCIL_DESC desc = { 0 };
	desc.DepthEnable = true;						   //Z�e�X�g���L���B
	desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO; //Z�o�b�t�@��Z�l��`�����܂Ȃ��B
	desc.DepthFunc = D3D11_COMPARISON_GREATER;		   //Z�l���傫����΃t���[���o�b�t�@�ɕ`�����ށB

	pd3d->CreateDepthStencilState(&desc, &m_silhouettoDepthStepsilState);
}


void __cdecl ModelEffect::Apply(ID3D11DeviceContext* deviceContext)
{
	//deviceContext->VSSetShader((ID3D11VertexShader*)m_pVSShader->GetBody(), NULL, 0);
	//deviceContext->PSSetShader((ID3D11PixelShader*)m_pPSShader->GetBody(), NULL, 0);
	//deviceContext->PSSetShaderResources(enSkinModelSRVReg_AlbedoTexture, 1, &m_albedoTex);

	switch (m_renderMode)
	{
		
	case enRenderMode_Normal:		//�ʏ�`��B
		deviceContext->VSSetShader((ID3D11VertexShader*)m_pVSShader->GetBody(), NULL, 0);
		deviceContext->PSSetShader((ID3D11PixelShader*)m_pPSShader->GetBody(), NULL, 0);
		deviceContext->PSSetShaderResources(enSkinModelSRVReg_AlbedoTexture, 1, &m_albedoTex);

		break;

	case enRenderMode_CreateShadowMap:	//�V���G�b�g�`��B�V���h�E�}�b�v�B

		deviceContext->VSSetShader((ID3D11VertexShader*)m_vsShadowMap.GetBody(), NULL, 0);
		deviceContext->PSSetShader((ID3D11PixelShader*)m_psShadowMap.GetBody(), NULL, 0);
		//�f�v�X�X�e���V���X�e�[�g��؂�ւ���B
		//deviceContext->OMSetDepthStencilState(m_silhouettoDepthStepsilState, 0);
		break;

	
	}

}