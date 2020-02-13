#include "stdafx.h"
#include "GameObjectManager.h"

#define USE_MAIN_RT		//��`����ƃ��C�������_�����O�^�[�Q�b�g���g����B

GameObjectManager::GameObjectManager()
{
	for (int i = 0; i < priorityMax; i++) { //�D��x�B
		m_gameObjectListArray.push_back(GameObjectList()); //���X�g�Ƀ��X�g�����Ă����BVector.
	}

	//�����_�����O�^�[�Q�b�g���쐬�B
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

	//���C�������_�����O�^�[�Q�b�g�ɕ`���ꂽ�G��
	//�t���[���o�b�t�@�ɃR�s�[���邽�߂̃X�v���C�g������������B
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
	//Delete�B
	ExecuteDeleteGameObjects();

	//Start�������I�B(�����𖞂�������)�B
	for (GameObjectList objectList : m_gameObjectListArray)
	{
		for (GameObject* obj : objectList)
		{
			obj->StartWrapper();
		}
	}

	//Update�������I�B(�����𖞂�������)�B
	for (GameObjectList objectList : m_gameObjectListArray)
	{
		for (GameObject* obj : objectList)
		{
			obj->UpdateWrapper();

		}
	}

	//�V���h�E�}�b�v���X�V�B
	m_shadowMap.Update({ 500.f,1000.0f,-500.0f }, { 0.0f,0.0f,0.0f });

	//�`��J�n�B
	g_graphicsEngine->BegineRender();

	//�t���[���o�b�t�@�̃����_�����O�^�[�Q�b�g���o�b�N�A�b�v���Ă����B
	auto d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
	ID3D11RenderTargetView* oldRenderTargetView;
	ID3D11DepthStencilView* oldDepthStencilView;
	d3dDeviceContext->OMGetRenderTargets(
		1,
		&oldRenderTargetView,
		&oldDepthStencilView
	);

	//�r���[�|�[�g���o�b�N�A�b�v������Ă����B
	unsigned int numViewport = 1;
	D3D11_VIEWPORT oldViewports;
	d3dDeviceContext->RSGetViewports(&numViewport, &oldViewports);
	//�V���h�E�}�b�v�Ƀ����_�����O
	m_shadowMap.RenderToShadowMap();
	
#ifdef USE_MAIN_RT
	//�����_�����O�^�[�Q�b�g�����C���ɕύX����B
	ChangeRenderTarget(d3dDeviceContext, &m_mainRenderTarget, &m_frameBufferViewports);
#else
	//�����_�����O�^�[�Q�b�g��߂��B
	//�����_�����O�^�[�Q�b�g�����C���ɕύX����B
	d3dDeviceContext->OMSetRenderTargets(
		1,
		&oldRenderTargetView,
		oldDepthStencilView
	);
	d3dDeviceContext->RSSetViewports(numViewport, &oldViewports);
	//�����_�����O�^�[�Q�b�g�ƃf�v�X�X�e���V���̎Q�ƃJ�E���^�������B
	oldRenderTargetView->Release();
	oldDepthStencilView->Release();
#endif
	//���C�������_�����O�^�[�Q�b�g���N���A����B

	float clearColor[] = { 0.6f, 0.8f, 1.0f, 1.0f };			//�w�i�F�B(���̓p�X�e���u���[)�B
	m_mainRenderTarget.ClearRenderTarget(clearColor);			//�w�i�����߂��F�ɁB

	//�RD�����_�����O�B
	//�ʏ탌���_�����O�B
	for (GameObjectList objList : m_gameObjectListArray)
	{
		for (GameObject* object : objList)
		{
			object->RenderWrapper();
		}
	}
	//���Ƃ����炱���Ń|�X�g�G�t�F�N�g�B

	g_graphicsEngine->DrawPostEffect();

	//�QD�̃����_�����O�B
	for (GameObjectList objList : m_gameObjectListArray)
	{
		for (GameObject* object : objList)
		{
			object->RenderAfterPostEffectWrapper();
		}
	}

#ifdef USE_MAIN_RT
	//�����_�����O�^�[�Q�b�g��߂��B
	//�����_�����O�^�[�Q�b�g����ʂɕύX����B
	d3dDeviceContext->OMSetRenderTargets(
		1,
		&oldRenderTargetView,
		oldDepthStencilView
	);
	d3dDeviceContext->RSSetViewports(numViewport, &oldViewports);
	//�����_�����O�^�[�Q�b�g�ƃf�v�X�X�e���V���̎Q�ƃJ�E���^�������B
	oldRenderTargetView->Release();
	oldDepthStencilView->Release();
#endif

	//m_mainRenderTarget�������_�����O�^�[�Q�b�g�B
	m_copyMainRtToFrameBufferSprite.Update(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());
	camera2d.Update();

	m_copyMainRtToFrameBufferSprite.Draw(&camera2d);

	//�QD�̃����_�����O�B
	for (GameObjectList objList : m_gameObjectListArray)
	{
		for (GameObject* object : objList)
		{
			object->PostRenderWrapper();
		}
	}

	//FontRender���g��Ȃ��t�H���g�̃����_�����O�B
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
	//�����_�����O�^�[�Q�b�g�̐؂�ւ��B
	d3dDeviceContext->OMSetRenderTargets(1, rtTbl, depthStensil);
	if (viewport != nullptr) {
		//�r���[�|�[�g���w�肳��Ă�����A�r���[�|�[�g���ύX����B
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

//�t�H���[�h�����_�����O�B
void GameObjectManager::ForwardRender()
{
	//�����_�����O�^�[�Q�b�g�����C���ɕύX����B
	auto d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
	ChangeRenderTarget(d3dDeviceContext, &m_mainRenderTarget, &m_frameBufferViewports);
	//���C�������_�����O�^�[�Q�b�g���N���A����B
	float clearColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	m_mainRenderTarget.ClearRenderTarget(clearColor);
}

void GameObjectManager::ExecuteDeleteGameObjects()
{
	int preBufferNo = m_currentDeleteObjectBufferNo;
	//�o�b�t�@��؂�ւ��B
	m_currentDeleteObjectBufferNo = 1 ^ m_currentDeleteObjectBufferNo;
	for (GameObjectList& goList : m_deleteObjectArray) {
		for (GameObject* go : goList) {
			GameObjectPriority priority = go->GetPriority();
			GameObjectList& goExecList = m_gameObjectListArray.at(priority);
			auto it = std::find(goExecList.begin(), goExecList.end(), go);

			auto index = std::distance(goExecList.begin(), it);


			if (it != goExecList.end()) {
				//�폜���X�g���珜�O���ꂽ�B
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