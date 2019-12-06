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

	if (m_isShadowCaster) {
		IGameObjectManager().AddShadowCaster(&m_skinModel);
	}

	m_animation.Update(1/60.0f);
	m_skinModel.UpdateWorldMatrix(m_position, m_rotation, m_scale);

}

void SkinModelRender::Render()
{
	if (m_drawAfterPostEffect == false) {			//ポストエフェクト前に書くなら。	
		//todo シャドウマップをレジスタに渡す。
		m_skinModel.SetShadowMap(IGameObjectManager().GetShadowMap()->GetShadowMapSRV());
		//todo InitされなかったらDrawを呼ばないようにする。 
		m_skinModel.Draw(enRenderMode_Normal, g_camera3D.GetViewMatrix(), g_camera3D.GetProjectionMatrix());
	}
}

void SkinModelRender::RenderAfterPostEffect()
{
	if (m_drawAfterPostEffect) {				//ポストエフェクト後に書くなら。
		m_skinModel.Draw(enRenderMode_Normal, g_camera3D.GetViewMatrix(), g_camera3D.GetProjectionMatrix());
		m_rotation = g_camera3D.GetCameraQuauternion();
		m_skinModel.SetShadowReciever(false);
	}
}

void SkinModelRender::Init(const wchar_t* filePath,
	AnimationClip* animationClips,
	int numAnimationClips, const char* psmain,
	const char* vsmain, bool drawAfterPostEffect)
{
	m_skinModel.Init(filePath, m_psmain, m_vsmain);
	InitAnimation(animationClips, numAnimationClips);
	ChangeDrawAfterPostEffect(drawAfterPostEffect);
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