#include "stdafx.h"
#include "SkinModelRender.h"

//todo 法線マップ。
ID3D11ShaderResourceView* g_normalMapSRV = nullptr;

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
	m_skinModel.UpdateWorldMatrix(m_position, m_rotation, m_scale);		//モデルをワールド座標系に変換するためのワールド行列を更新。

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
		m_rotation = g_camera3D.GetCameraQuauternion();			//カメラの回転をモデルの回転軸に代入。(モデルが正面に向くため2Dに見える)。
		m_skinModel.SetShadowReciever(false);					//影がかからない。
		SetShadowCasterFlag(false);								//影を出さない。
		m_skinModel.Draw(enRenderMode_Normal, g_camera3D.GetViewMatrix(), g_camera3D.GetProjectionMatrix());		//更新処理。
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

void SkinModelRender::InitNormalMap(const wchar_t* filePath)
{
	//m_skinModel.InitNormalMap(filePath);
	//ファイル名を使って、テクスチャをロードして、ShaderResrouceViewを作成する。
	DirectX::CreateDDSTextureFromFileEx(
		g_graphicsEngine->GetD3DDevice(),
		filePath,	//ロードするテクスチャのパス。
		0,
		D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE,
		0,
		0,
		false,
		nullptr,
		&g_normalMapSRV						//作成されたSRVのアドレスの格納先。
	);

	//モデルに法線マップを設定する。
	m_skinModel.SetNormalMap(g_normalMapSRV);
	
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

