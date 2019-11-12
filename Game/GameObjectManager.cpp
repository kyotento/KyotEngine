#include "stdafx.h"
#include "GameObjectManager.h"

GameObjectManager::GameObjectManager()
{
	for (int i = 0; i < priorityMax; i++) { //�D��x�B
		m_gameObjectListArray.push_back(GameObjectList()); //���X�g�Ƀ��X�g�����Ă����BVector.
	}
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
	m_shadowMap.Update({ 1000.0f,1000.0f,1000.0f }, { 0.0f,0.0f,0.0f });

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

	//todo todotodotodotodotodotodo9

	//�ʏ탌���_�����O�B
	for (GameObjectList objList : m_gameObjectListArray)
	{
		for (GameObject* object : objList)
		{
			object->RenderWrapper();
		}
	}

	g_graphicsEngine->EndRender();

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
			if (it != goExecList.end()) {
				//�폜���X�g���珜�O���ꂽ�B
				(*it)->SetRegistDeadList(false);
				if ((*it)->GetNewGameObjectManager()) {
					delete (*it);
				}
			}
			goExecList.erase(it);
		}
		goList.clear();
	}
}