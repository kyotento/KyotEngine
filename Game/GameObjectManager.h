#pragma once
#define _CGAMEOBJECTMANAGER_H_
#include "GameObject.h"
#include "util/Util.h"
class GameObjectManager /*: public Noncopy*/
{
public:
	/// <summary>
	/// �R���X�g���N�^�B
	/// </summary>
	GameObjectManager();

	/// <summary>
	/// �f�X�g���N�^�B
	/// </summary>
	~GameObjectManager();

	/*
	template <class T>
	
	/// <summary>
	/// NewGO�B
	/// </summary>
	/// <param name="m_priority">���s�D��x�B</param>
	/// <param name=""></param>
	/// <returns></returns>
	T* NewGO(GameObjectPriority m_priority, const wchar_t*)
	{
		T* object = new T();
		m_gameObjectListArray[m_priority].push_back(object);
		return object;
	}
	*/
	//Execute�BGOM�̃A�b�v�f�[�g�̂悤�Ȃ��́B


	/// <summary>
	/// �Q�[���I�u�W�F�N�g�̖��O�L�[���쐬�B
	/// </summary>
	/// <param name="objectName">�I�u�W�F�N�g�̖��O</param>
	/// <returns>���O�L�[</returns>
	static unsigned int MakeGameObjectNameKey(const char* objectName)
	{
		static const unsigned int defaultNameKey = Util::MakeHash("Undefined");	//���O�L�[�B
		unsigned int hash;

		if (objectName == nullptr) {
			hash = defaultNameKey;
		}

		else {
			hash = Util::MakeHash(objectName);
		}
		return hash;
	}

	/// <summary>
	/// �Q�[���I�u�W�F�N�g�̒ǉ��B
	/// </summary>
	/// <param name="priority">���s�D��x</param>
	/// <param name="gameobject">GameObject</param>
	/// <param name="objName">�I�u�W�F�N�g�̖��O</param>
	/// <remarks>
	/// GameObjectManager�ɓo�^����Ă��Ȃ������ꍇ
	/// {
	///		�I�u�W�F�N�g�̖��O�L�[���쐬�B
	///		�D��x�t�����X�g�Ɏ��s�D��x������B
	///		���s�D��x�̐ݒ�B
	///		Start�t���O���������B
	///		NameKey��ݒ肷��B
	/// }
	/// ���S�t���O�������Ă����ꍇ�B
	/// {
	///		���O����B
	/// }
	/// </remarks>
	void AddGameObject(GameObjectPriority priority, GameObject* gameobject, const char* objName = nullptr)
	{

		if (!gameobject->GetRegistration) {

			unsigned int namekey = MakeGameObjectNameKey(objName);
			m_gameObjectListArray.at(priority).push_back(gameobject);
			gameobject->SetRegistration(true);
			gameobject->SetPriority(priority);
			gameobject->SetStart(false);
			gameobject->SetNameKey(namekey);
			if (gameobject->IsDead)
			{
				gameobject->SetDeadFlag(false);
			}
			
		}
	}

private:

	int priorityMax = 32;                            //�D��x�̏���l�B

	typedef std::list<GameObject*>	GameObjectList;                     //���X�g�̐e���B
	std::vector<GameObjectList>	m_gameObjectListArray;					//�Q�[���I�u�W�F�N�g�̗D��x�t�����X�g�B

	
};

