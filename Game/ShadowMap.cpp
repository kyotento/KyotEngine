#include "stdafx.h"
#include "ShadowMap.h"

//todo �Z�@�\�t�g�V���h�E��������B

ShadowMap::ShadowMap()
{
	//�V���h�E�}�b�v�����p�̃����_�����O�^�[�Q�b�g���쐬�B
	m_shadowMapRT.Create(
		4096,
		4096,
		DXGI_FORMAT_R32_FLOAT
	);
}

ShadowMap::~ShadowMap()
{
}

void ShadowMap::Update(CVector3 lightCameraPos, CVector3 lightCameraTarget)
{
	m_lightCameraTarget = lightCameraTarget;
	m_lightCameraPosition = lightCameraPos;

	//���C�g�̕������v�Z����B
	auto lightDir = m_lightCameraTarget - m_lightCameraPosition;
	if (lightDir.Length() < 0.00001f) {
		//�����_�Ǝ��_���߂�����ƃo�O���������邽�߁A�N���b�V��������B
		std::abort();
	}

	//�����x�N�g���ɕϊ��B
	lightDir.Normalize();

	//���C�g�J�����̏㉺�����̌���B
	CVector3 lightCameraUpAxis;
	if (fabsf(lightDir.y) > 0.999998f)
	{
		lightCameraUpAxis = CVector3::AxisX();
	}
	else {
		lightCameraUpAxis = CVector3::AxisY();
	}

	//���C�g�r���[�s����v�Z����B
	m_lightViewMatrix.MakeLookAt(
		m_lightCameraPosition,
		m_lightCameraTarget,
		lightCameraUpAxis
	);

	//���C�g�v���W�F�N�V�����s����쐬����B
	m_lightProjMatrix.MakeOrthoProjectionMatrix(
		3000,
		3000,
		10.0f,
		5000.0f
	);
}
void ShadowMap::RenderToShadowMap()
{
	auto d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
	//�����_�����O�^�[�Q�b�g��؂�ւ���B
	ID3D11RenderTargetView* rts[] = {
		m_shadowMapRT.GetRenderTargetView()
	};
	d3dDeviceContext->OMSetRenderTargets(1, rts, m_shadowMapRT.GetDepthStensilView());
	//�r���[�|�[�g��ݒ�B
	d3dDeviceContext->RSSetViewports(1, m_shadowMapRT.GetViewport());
	//�V���h�E�}�b�v���N���A�B
	//��ԉ���Z��1.0�Ȃ̂ŁA1.0�œh��Ԃ��B
	float clearColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f }; //red,green,blue,alpha
	m_shadowMapRT.ClearRenderTarget(clearColor);

	//�V���h�E�L���X�^�[���V���h�E�}�b�v�Ƀ����_�����O�B
	for (auto& caster : m_shadowCasters) {
		caster->Draw(
			enRenderMode_CreateShadowMap,
			m_lightViewMatrix,
			m_lightProjMatrix
		);
	}
	//�L���X�^�[���N���A�B
	m_shadowCasters.clear();
}
