#pragma once
#define _CGAMEOBJECTMANAGER_H_
class GameObjectManager /*: public Noncopy*/
{
public:
	GameObjectManager();
	~GameObjectManager();

	//NewGO。
	template <class T>
	T* NewGO(GameObjectPriority m_priority, const wchar_t*)
	{
		T* object = new T();
		m_gameObjectListArray[m_priority].push_back(object);
		return object;
	}

	//Execute。GOMのアップデートのようなもの。

private:

	int priorityMax = 32;                            //優先度の上限値。

	typedef std::list<GameObject*>	GameObjectList;                     //リストの親分。
	std::vector<GameObjectList>	m_gameObjectListArray;					//ゲームオブジェクトの優先度付きリスト。


};

