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
/// �C���X�^���X�̎擾�B
/// </summary>
/// <returns>�C���X�^���X</returns>
	static GameObjectManager& Instance()
	{
		static GameObjectManager instance;
		return instance;
	}



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

		if (!gameobject->GetRegistration()) {

			unsigned int namekey = MakeGameObjectNameKey(objName);
			m_gameObjectListArray.at(priority).push_back(gameobject);
			gameobject->SetRegistration(true);
			gameobject->SetPriority(priority);
			gameobject->SetStart(false);
			gameobject->SetNameKey(namekey);
			if (gameobject->IsDead())
			{
				gameobject->SetDeadFlag(false);
			}
			
		}
	}


	/// <summary>
	/// �Q�[���I�u�W�F�N�g��New�B
	/// </summary>
	/// <param name="priority">�W�I���D��x</param>
	/// <param name="objectName">�I�u�W�F�N�g�̖��O</param>
	/// <param name="...ctorArgs">�ϒ�����(�R���X�g���N�^�ɓn��)</param>
	/// <returns>�I�u�W�F�N�g</returns>
	/// <remarks>
	/// New����B
	/// 
	/// </remarks>
	template<class T, class... TArgs>
	T* NewGameObject(GameObjectPriority priority, const char* objectName, TArgs... ctorArgs)
	{

		T* newObject = new T(ctorArgs...);
		newObject->SetNewGameObjectManager();
		m_gameObjectListArray.at(priority).push_back(newObject);
		unsigned int hash = MakeGameObjectNameKey(objectName);
		newObject->SetRegistration(true);
		newObject->SetPriority(priority);
		newObject->SetNameKey(hash);

		return newObject;

	}

	/// <summary>
	/// GameObject�̍폜�B
	/// </summary>
	/// <param name="gameobject">GameObject</param>
	/// <remarks>
	/// GameObject�����݂��Ă��邩�AGameObjectManager��NE������Ă���Ƃ��B
	///		���S�t���O�𗧂Ă�B
	///		GameObjectManager�Œǉ����ꂽ�B
	///		���S���X�g�ɐς܂ꂽ�B
	///		�D��x�t�����X�g�Ɍ��݂̏����I�u�W�F�N�g���i�[�BPriority���B
	///		gameobject��null�ɁB
	/// </remarks>
	void DeleteGameObject(GameObject* gameobject)
	{

		if (gameobject != nullptr && gameobject->GetRegistration())
		{

			gameobject->SetDeadFlag(true);
			gameobject->SetRegistration(false);
			gameobject->SetRegistDeadList(true);

			m_deleteObjectArray[m_currentDeleteObjectBufferNo].push_back(gameobject);
			gameobject = nullptr;

		}

	}
	/// <summary>
	/// �X�V�֐��B
	/// </summary>
	void Execute();

private:

	int priorityMax = 32;                           //�D��x�̏���l�B
	int m_currentDeleteObjectBufferNo = 0;			//���݂̍폜�I�u�W�F�N�g�̃o�b�t�@�ԍ��B

	void Start();
	void Update();

	typedef std::list<GameObject*>	GameObjectList;                     //���X�g�̐e���B
	std::vector<GameObjectList>	m_gameObjectListArray;					//�Q�[���I�u�W�F�N�g�̗D��x�t�����X�g�B
	GameObjectList	m_deleteObjectArray[2];					//�폜����I�u�W�F�N�g�̃��X�g�B�폜�������s���Ă���Œ���DeleteGameObject���Ă΂��\���������̂ŁA�_�u���o�b�t�@���B



	D3D11_VIEWPORT m_frameBufferViewports;								//�t���[���o�b�t�@�̃r���[�|�[�g�B
	ID3D11RenderTargetView* m_frameBufferRenderTargetView = nullptr;	//�t���[���o�b�t�@�̃����_�����O�^�[�Q�b�g�r���[�B
	ID3D11DepthStencilView* m_frameBufferDepthStencilView = nullptr;	//�t���[���o�b�t�@�̃f�v�X�X�e���V���r���[�B

};


/// <summary>
/// 
/// </summary>
/// <returns></returns>
static inline GameObjectManager& IGameObjectManager()
{
	return GameObjectManager::Instance();
}


/// <summary>
/// �Q�[���I�u�W�F�N�g�̐������ȒP�ɂł���悤�ɂ��邽�߂̊֐��B
/// </summary>
/// <param name="priority">���s�D��x</param>
/// <param name="objectName">�I�u�W�F�N�g�̖��O</param>
/// <param name="...ctorArgs">�ϒ�����(�R���X�g���N�^�ɓn��)</param>
/// <returns>NewGameObject�̈���</returns>
template<class T, class... TArgs>
static inline T* NewGO(GameObjectPriority priority, const char* objectName, TArgs... ctorArgs)
{
	return IGameObjectManager().NewGameObject<T>((GameObjectPriority)priority, objectName, ctorArgs...);

}


/// <summary>
/// �Q�[���I�u�W�F�N�g�̍폜���ȒP�ɂł���悤�ɂ��邽�߂̊֐��B
/// </summary>
/// <param name="go">GAmeObject</param>
static inline void DeleteGO(GameObject* gameobject)
{
	IGameObjectManager().DeleteGameObject(gameobject);
}