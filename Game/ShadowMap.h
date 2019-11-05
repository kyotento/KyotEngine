#pragma once 

#include "RenderTarget.h"

class ShadowMap
{
public:
	ShadowMap();
	~ShadowMap();

	/// <summary>
/// ライトビュー行列を取得。
/// </summary>
/// <returns></returns>
	CMatrix GetLighViewMatrix()
	{
		return m_lightViewMatrix;
	}
	/// <summary>
	/// ライトプロジェクション行列を取得。
	/// </summary>
	/// <returns></returns>
	CMatrix GetLightProjMatrix()
	{
		return m_lightProjMatrix;
	}

	/// <summary>
	/// 更新処理。
	/// </summary>
	/// <param name="lightCameraPos">ライトカメラの視点座標</param>
	/// <param name="lightCameraTarget">ライトカメラんp注視点の座標</param>
	void Update(CVector3 lightCameraPos, CVector3 lightCameraTarget);

	/// <summary>
	/// シャドウマップに描画されるシャドウキャスター。
	/// </summary>
	void RenderToShadowMap();

	/// <summary>
	/// シャドウキャスターを登録。
	/// </summary>
	/// <param name="shadowCaster">シャドウキャスター</param>
	void RegistShadowCaster(SkinModel* shadowCaster)
	{
		m_shadowCasters.push_back(shadowCaster);
	}

private:
	CVector3 m_lightCameraPosition = CVector3::Zero();	//ライトカメラの視点。
	CVector3 m_lightCameraTarget = CVector3::Zero();	//ライトカメラの注視点。
	CMatrix m_lightViewMatrix = CMatrix::Identity();	//ライトビュー行列。
	CMatrix m_lightProjMatrix = CMatrix::Identity();	//ライトプロジェクション行列。
	RenderTarget m_shadowMapRT;						//シャドウマップを描画するレンダリングターゲット。
	std::vector< SkinModel*> m_shadowCasters;	//シャドウキャスターの配列。

};

