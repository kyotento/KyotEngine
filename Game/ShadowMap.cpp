#include "stdafx.h"
#include "ShadowMap.h"

//todo 技　ソフトシャドウ実装する。

ShadowMap::ShadowMap()
{
	//シャドウマップ生成用のレンダリングターゲットを作成。
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

	//ライトの方向を計算する。
	auto lightDir = m_lightCameraTarget - m_lightCameraPosition;
	if (lightDir.Length() < 0.00001f) {
		//注視点と視点が近すぎるとバグが発生するため、クラッシュさせる。
		std::abort();
	}

	//方向ベクトルに変換。
	lightDir.Normalize();

	//ライトカメラの上下方向の決定。
	CVector3 lightCameraUpAxis;
	if (fabsf(lightDir.y) > 0.999998f)
	{
		lightCameraUpAxis = CVector3::AxisX();
	}
	else {
		lightCameraUpAxis = CVector3::AxisY();
	}

	//ライトビュー行列を計算する。
	m_lightViewMatrix.MakeLookAt(
		m_lightCameraPosition,
		m_lightCameraTarget,
		lightCameraUpAxis
	);

	//ライトプロジェクション行列を作成する。
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
	//レンダリングターゲットを切り替える。
	ID3D11RenderTargetView* rts[] = {
		m_shadowMapRT.GetRenderTargetView()
	};
	d3dDeviceContext->OMSetRenderTargets(1, rts, m_shadowMapRT.GetDepthStensilView());
	//ビューポートを設定。
	d3dDeviceContext->RSSetViewports(1, m_shadowMapRT.GetViewport());
	//シャドウマップをクリア。
	//一番奥のZは1.0なので、1.0で塗りつぶす。
	float clearColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f }; //red,green,blue,alpha
	m_shadowMapRT.ClearRenderTarget(clearColor);

	//シャドウキャスターをシャドウマップにレンダリング。
	for (auto& caster : m_shadowCasters) {
		caster->Draw(
			enRenderMode_CreateShadowMap,
			m_lightViewMatrix,
			m_lightProjMatrix
		);
	}
	//キャスターをクリア。
	m_shadowCasters.clear();
}
