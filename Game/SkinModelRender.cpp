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

	if (m_isShadowCaster) {				//フラグがtrueなら。
		IGameObjectManager().AddShadowCaster(&m_skinModel);			//シャドウキャスターに書き込む。
	}

	m_animation.Update(1/60.0f);			//アニメーション。
	m_skinModel.UpdateWorldMatrix(m_position, m_rotation, m_scale);

}

//3Dモデルの描画処理
void SkinModelRender::Render()
{
	if (m_drawAfterPostEffect == false) {			//ポストエフェクト前に書くなら。	
		//todo シャドウマップをレジスタに渡す。
		m_skinModel.SetShadowMap(IGameObjectManager().GetShadowMap()->GetShadowMapSRV());
		//todo InitされなかったらDrawを呼ばないようにする。 
		m_skinModel.Draw(enRenderMode_Normal, g_camera3D.GetViewMatrix(), g_camera3D.GetProjectionMatrix());
	}
}

//3DのSpriteの描画処理。(ポストエフェクトの影響を受けない)。
void SkinModelRender::RenderAfterPostEffect()
{
	if (m_drawAfterPostEffect) {				//ポストエフェクト後に書くなら。
		m_skinModel.Draw(enRenderMode_Normal, g_camera3D.GetViewMatrix(), g_camera3D.GetProjectionMatrix());		//更新処理。
		m_rotation = g_camera3D.GetCameraQuauternion();			//カメラの回転をモデルの回転軸に代入。(モデルが正面に向くため2Dに見える)。
		m_skinModel.SetShadowReciever(false);					//影がかからない。
		SetShadowCasterFlag(false);								//影を出さない。
	}
}

//初期化。
void SkinModelRender::Init(const wchar_t* filePath,
	AnimationClip* animationClips,
	int numAnimationClips, const char* psmain,
	const char* vsmain, bool drawAfterPostEffect, bool SetShadowReciever)
{
	//スキンモデルの初期化に代入。
	m_skinModel.Init(filePath, m_psmain, m_vsmain/*, SetShadowReciever*/);
	InitAnimation(animationClips, numAnimationClips);			//アニメーションの初期化。
	ChangeDrawAfterPostEffect(drawAfterPostEffect);				//2Dとして描画するかどうか。
	m_skinModel.SetShadowReciever(SetShadowReciever);			//影がかかるかどうか。
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