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
