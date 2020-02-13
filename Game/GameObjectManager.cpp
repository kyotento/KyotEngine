#include "stdafx.h"
#include "GameObjectManager.h"

#define USE_MAIN_RT		//定義するとメインレンダリングターゲットが使われる。

GameObjectManager::GameObjectManager()
{
	for (int i = 0; i < priorityMax; i++) { //優先度。
		m_gameObjectListArray.push_back(GameObjectList()); //リストにリストを入れていく。Vector.
	}

	//レンダリングターゲットを作成。
	m_mainRenderTarget.Create(
		FRAME_BUFFER_W,
		FRAME_BUFFER_H,
		DXGI_FORMAT_R16G16B16A16_FLOAT
	);
	m_frameBufferViewports.TopLeftX = 0;
	m_frameBufferViewports.TopLeftY = 0;
	m_frameBufferViewports.Width = FRAME_BUFFER_W;
	m_frameBufferViewports.Height = FRAME_BUFFER_H;
	m_frameBufferViewports.MinDepth = 0.0f;
	m_frameBufferViewports.MaxDepth = 1.0f;

	//メインレンダリングターゲットに描かれた絵を
	//フレームバッファにコピーするためのスプライトを初期化する。
	m_copyMainRtToFrameBufferSprite.Init(
		m_mainRenderTarget.GetRenderTargetSRV(),
		FRAME_BUFFER_W,
		FRAME_BUFFER_H
	);

}

GameObjectManager::~GameObjectManager()
{
}


void GameObjectManager::Execute()
{
	//Delete。
	ExecuteDeleteGameObjects();

	//Startすっぞ！。(条件を満たせたら)。
	for (GameObjectList objectList : m_gameObjectListArray)
	{
		for (GameObject* obj : objectList)
		{
			obj->StartWrapper();
		}
	}

	//Updateすっぞ！。(条件を満たせたら)。
	for (GameObjectList objectList : m_gameObjectListArray)
	{
		for (GameObject* obj : objectList)
		{
			obj->UpdateWrapper();

		}
	}

	//シャドウマップを更新。
	m_shadowMap.Update({ 500.f,1000.0f,-500.0f }, { 0.0f,0.0f,0.0f });

	//描画開始。
	g_graphicsEngine->BegineRender();

	//フレームバッファのレンダリングターゲットをバックアップしておく。
	auto d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
	ID3D11RenderTargetView* oldRenderTargetView;
	ID3D11DepthStencilView* oldDepthStencilView;
	d3dDeviceContext->OMGetRenderTargets(
		1,
		&oldRenderTargetView,
		&oldDepthStencilView
	);

	//ビューポートもバックアップを取っておく。
	unsigned int numViewport = 1;
	D3D11_VIEWPORT oldViewports;
	d3dDeviceContext->RSGetViewports(&numViewport, &oldViewports);
	//シャドウマップにレンダリング
	m_shadowMap.RenderToShadowMap();
	
#ifdef USE_MAIN_RT
	//レンダリングターゲットをメインに変更する。
	ChangeRenderTarget(d3dDeviceContext, &m_mainRenderTarget, &m_frameBufferViewports);
#else
	//レンダリングターゲットを戻す。
	//レンダリングターゲットをメインに変更する。
	d3dDeviceContext->OMSetRenderTargets(
		1,
		&oldRenderTargetView,
		oldDepthStencilView
	);
	d3dDeviceContext->RSSetViewports(numViewport, &oldViewports);
	//レンダリングターゲットとデプスステンシルの参照カウンタを下す。
	oldRenderTargetView->Release();
	oldDepthStencilView->Release();
#endif
	//メインレンダリングターゲットをクリアする。

	float clearColor[] = { 0.6f, 0.8f, 1.0f, 1.0f };			//背景色。(今はパステルブルー)。
	m_mainRenderTarget.ClearRenderTarget(clearColor);			//背景を決めた色に。

	//３Dレンダリング。
	//通常レンダリング。
	for (GameObjectList objList : m_gameObjectListArray)
	{
		for (GameObject* object : objList)
		{
			object->RenderWrapper();
		}
	}
	//やるとしたらここでポストエフェクト。

	g_graphicsEngine->DrawPostEffect();

	//２Dのレンダリング。
	for (GameObjectList objList : m_gameObjectListArray)
	{
		for (GameObject* object : objList)
		{
			object->RenderAfterPostEffectWrapper();
		}
	}

#ifdef USE_MAIN_RT
	//レンダリングターゲットを戻す。
	//レンダリングターゲットを画面に変更する。
	d3dDeviceContext->OMSetRenderTargets(
		1,
		&oldRenderTargetView,
		oldDepthStencilView
	);
	d3dDeviceContext->RSSetViewports(numViewport, &oldViewports);
	//レンダリングターゲットとデプスステンシルの参照カウンタを下す。
	oldRenderTargetView->Release();
	oldDepthStencilView->Release();
#endif

	//m_mainRenderTargetをレンダリングターゲット。
	m_copyMainRtToFrameBufferSprite.Update(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());
	camera2d.Update();

	m_copyMainRtToFrameBufferSprite.Draw(&camera2d);

	//２Dのレンダリング。
	for (GameObjectList objList : m_gameObjectListArray)
	{
		for (GameObject* object : objList)
		{
			object->PostRenderWrapper();
		}
	}

	//FontRenderを使わないフォントのレンダリング。
	for (GameObjectList objList : m_gameObjectListArray)
	{
		for (GameObject* object : objList)
		{
			object->AfterFontRenderWrapper();
		}
	}

//	g_physics.DebugDraw();

	g_graphicsEngine->EndRender();

}

void GameObjectManager::ChangeRenderTarget(ID3D11DeviceContext* d3dDeviceContext, ID3D11RenderTargetView* renderTarget, ID3D11DepthStencilView* depthStensil, D3D11_VIEWPORT* viewport)
{
	ID3D11RenderTargetView* rtTbl[] = {
		renderTarget
	};
	//レンダリングターゲットの切り替え。
	d3dDeviceContext->OMSetRenderTargets(1, rtTbl, depthStensil);
	if (viewport != nullptr) {
		//ビューポートが指定されていたら、ビューポートも変更する。
		d3dDeviceContext->RSSetViewports(1, viewport);
	}
}

void GameObjectManager::ChangeRenderTarget(ID3D11DeviceContext* d3dDeviceContext, RenderTarget* renderTarget, D3D11_VIEWPORT* viewport)
{
	ChangeRenderTarget(
		d3dDeviceContext,
		renderTarget->GetRenderTargetView(),
		renderTarget->GetDepthStensilView(),
		viewport
	);
}

//フォワードレンダリング。
void GameObjectManager::ForwardRender()
{
	//レンダリングターゲットをメインに変更する。
	auto d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
	ChangeRenderTarget(d3dDeviceContext, &m_mainRenderTarget, &m_frameBufferViewports);
	//メインレンダリングターゲットをクリアする。
	float clearColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	m_mainRenderTarget.ClearRenderTarget(clearColor);
}

void GameObjectManager::ExecuteDeleteGameObjects()
{
	int preBufferNo = m_currentDeleteObjectBufferNo;
	//バッファを切り替え。
	m_currentDeleteObjectBufferNo = 1 ^ m_currentDeleteObjectBufferNo;
	for (GameObjectList& goList : m_deleteObjectArray) {
		for (GameObject* go : goList) {
			GameObjectPriority priority = go->GetPriority();
			GameObjectList& goExecList = m_gameObjectListArray.at(priority);
			auto it = std::find(goExecList.begin(), goExecList.end(), go);

			auto index = std::distance(goExecList.begin(), it);


			if (it != goExecList.end()) {
				//削除リストから除外された。
				(*it)->SetRegistDeadList(false);
				if ((*it)->GetNewGameObjectManager()) {
					delete (*it);
				}
				goExecList.erase(it);
			}
		}
		goList.clear();
	}
}