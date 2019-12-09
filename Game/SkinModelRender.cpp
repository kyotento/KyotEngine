#include "stdafx.h"
#include "SkinModelRender.h"

SkinModelRender::SkinModelRender()
{

}

SkinModelRender::~SkinModelRender()
{
}

bool SkinModelRender::Start()
{


	return true;
}

void SkinModelRender::Update()
{

	if (m_isShadowCaster) {				//�t���O��true�Ȃ�B
		IGameObjectManager().AddShadowCaster(&m_skinModel);			//�V���h�E�L���X�^�[�ɏ������ށB
	}

	m_animation.Update(1/60.0f);			//�A�j���[�V�����B
	m_skinModel.UpdateWorldMatrix(m_position, m_rotation, m_scale);

}

//3D���f���̕`�揈��
void SkinModelRender::Render()
{
	if (m_drawAfterPostEffect == false) {			//�|�X�g�G�t�F�N�g�O�ɏ����Ȃ�B	
		//todo �V���h�E�}�b�v�����W�X�^�ɓn���B
		m_skinModel.SetShadowMap(IGameObjectManager().GetShadowMap()->GetShadowMapSRV());
		//todo Init����Ȃ�������Draw���Ă΂Ȃ��悤�ɂ���B 
		m_skinModel.Draw(enRenderMode_Normal, g_camera3D.GetViewMatrix(), g_camera3D.GetProjectionMatrix());
	}
}

//3D��Sprite�̕`�揈���B(�|�X�g�G�t�F�N�g�̉e�����󂯂Ȃ�)�B
void SkinModelRender::RenderAfterPostEffect()
{
	if (m_drawAfterPostEffect) {				//�|�X�g�G�t�F�N�g��ɏ����Ȃ�B
		m_skinModel.Draw(enRenderMode_Normal, g_camera3D.GetViewMatrix(), g_camera3D.GetProjectionMatrix());		//�X�V�����B
		m_rotation = g_camera3D.GetCameraQuauternion();			//�J�����̉�]�����f���̉�]���ɑ���B(���f�������ʂɌ�������2D�Ɍ�����)�B
		m_skinModel.SetShadowReciever(false);					//�e��������Ȃ��B
		SetShadowCasterFlag(false);								//�e���o���Ȃ��B
	}
}

//�������B
void SkinModelRender::Init(const wchar_t* filePath,
	AnimationClip* animationClips,
	int numAnimationClips, const char* psmain,
	const char* vsmain, bool drawAfterPostEffect, bool SetShadowReciever)
{
	//�X�L�����f���̏������ɑ���B
	m_skinModel.Init(filePath, m_psmain, m_vsmain/*, SetShadowReciever*/);
	InitAnimation(animationClips, numAnimationClips);			//�A�j���[�V�����̏������B
	ChangeDrawAfterPostEffect(drawAfterPostEffect);				//2D�Ƃ��ĕ`�悷�邩�ǂ����B
	m_skinModel.SetShadowReciever(SetShadowReciever);			//�e�������邩�ǂ����B
}

void SkinModelRender::ChangeDrawAfterPostEffect(bool drawAfterPostEffect) 
{
	m_drawAfterPostEffect = drawAfterPostEffect;
}

void SkinModelRender::InitAnimation(AnimationClip* animationClips, int numAnimationClips) {
	m_animationClips = animationClips;
	m_numAnimationClips = numAnimationClips;
	if (m_animationClips != nullptr) {
		m_animation.Init(m_skinModel, m_animationClips, m_numAnimationClips);
	}
}