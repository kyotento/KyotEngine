#include "stdafx.h"
#include "GameObjectManager.h"


GameObjectManager::GameObjectManager()
{
	for (int i = 0; i < priorityMax; i++) { //優先度。
		m_gameObjectListArray.push_back(GameObjectList()); //リストにリストを入れていく。Vector.
	}
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

	//描画開始。
	g_graphicsEngine->BegineRender();


	//レンダリング。
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
	//バッファを切り替え。
	m_currentDeleteObjectBufferNo = 1 ^ m_currentDeleteObjectBufferNo;
	for (GameObjectList& goList : m_deleteObjectArray) {
		for (GameObject* go : goList) {
			GameObjectPriority priority = go->GetPriority();
			GameObjectList& goExecList = m_gameObjectListArray.at(priority);
			auto it = std::find(goExecList.begin(), goExecList.end(), go);
			if (it != goExecList.end()) {
				//削除リストから除外された。
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