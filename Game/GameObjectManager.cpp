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

	//�`��J�n�B
	g_graphicsEngine->BegineRender();


	//�����_�����O�B
	for (GameObjectList objList : m_gameObjectListArray)
	{
		for (GameObject* object : objList)
		{
			object->RenderWrapper();
		}
	}

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