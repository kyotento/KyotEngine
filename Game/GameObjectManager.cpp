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
