#pragma once
#define _CGAMEOBJECTMANAGER_H_
class GameObjectManager /*: public Noncopy*/
{
public:
	GameObjectManager();
	~GameObjectManager();

	//NewGO�B
	template <class T>
	T* NewGO(GameObjectPriority m_priority, const wchar_t*)
	{
		T* object = new T();
		m_gameObjectListArray[m_priority].push_back(object);
		return object;
	}

	//Execute�BGOM�̃A�b�v�f�[�g�̂悤�Ȃ��́B

private:

	int priorityMax = 32;                            //�D��x�̏���l�B

	typedef std::list<GameObject*>	GameObjectList;                     //���X�g�̐e���B
	std::vector<GameObjectList>	m_gameObjectListArray;					//�Q�[���I�u�W�F�N�g�̗D��x�t�����X�g�B


};

