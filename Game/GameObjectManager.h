#pragma once
#define _CGAMEOBJECTMANAGER_H_
//#define _SOUNDENGNE_	//�T�E���h�G���W�����g�p����Ƃ��ɒ�`�B
#include "GameObject.h"
#include "util/Util.h"
#include "ShadowMap.h"
#include "Sprite.h"
#include "Random.h"
#include "GameTime.h"
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
		static GameObjectManager* instance = nullptr;
		if (instance == nullptr) {
			instance = new GameObjectManager;
		}
		return *instance;
	}
	static void DeleteInstance()
	{
		delete &Instance();
	}

	void AddShadowCaster(SkinModel* model) {
		m_shadowMap.RegistShadowCaster(model);
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
	/// ���G���[�ł����ɔ�΂������ցB
	/// �@�@������#include���Ă�H�H�B
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

		if (gameobject != nullptr && gameobject->GetRegistration() && !gameobject->IsDead())
		{

			gameobject->SetDeadFlag(true);
			gameobject->SetRegistration(false);
			gameobject->SetRegistDeadList(true);

			m_deleteObjectArray[m_currentDeleteObjectBufferNo].push_back(gameobject);
			gameobject = nullptr;

		}

	}

	/// <summary>
	/// �Q�[���I�u�W�F�N�g�̌����B(�d����)�B
	/// </summary>
	/// <param name="ObjectName">�I�u�W�F�N�g�̖��O</param>
	/// <returns>�I�u�W�F�N�g</returns>
	template<class T>
	T* FindGameObject(const char* ObjectName)
	{
		unsigned int nameKey = Util::MakeHash(ObjectName);
		for (auto goList : m_gameObjectListArray)
		{
			for (auto go : goList)
			{
				if (go->GetNameKey() == nameKey)
				{
					T* po = dynamic_cast<T*>(go);
					if (po == nullptr)
					{
						//���s�B
					}
					return po;
				}
			}
		}
		//�����Ɉ���������Ȃ������Ƃ��B
		return nullptr;
	}


	/// <summary>
	/// �I�u�W�F�N�g�̌����B
	/// </summary>
	/// <param name="objectName">�I�u�W�F�N�g�̖��O</param>
	/// <param name="funk"></param>
	template<class T>
	void FindGameObjects(const char* objectName, std::function<bool(T*go)> func)
	{
		unsigned int nameKey = Util::MakeHash(objectName);
		for (auto goList : m_gameObjectListArray) {
			for (auto go : goList) {
				if (go->GetNameKey() == nameKey) {
					//�������B
					T* p = dynamic_cast<T*>(go);
					if (func(p) == false) {
						//�N�G�����f�B
						return;
					}
				}
			}
		}
	}


	/// <summary>
	/// �t�H���[�h�����_�����O�`�揈���B(�ʏ�`��)�B
	/// </summary>
	virtual void ForwardRender();


	/// <summary>
	/// �����_�����O�^�[�Q�b�g�؂�ւ��B
	/// </summary>
	/// <param name="d3dDeviceContext">D3D�f�o�C�X�R���e�L�X�g</param>
	/// <param name="renderTarget">�����_�����O�^�[�Q�b�g</param>
	/// <param name="viewport">�r���[�|�[�g</param>
	void ChangeRenderTarget(ID3D11DeviceContext* d3dDeviceContext, RenderTarget* renderTarget, D3D11_VIEWPORT* viewport);
	void ChangeRenderTarget(ID3D11DeviceContext* d3dDeviceContext, ID3D11RenderTargetView* renderTarget, ID3D11DepthStencilView* depthStensil, D3D11_VIEWPORT* viewport);


	/// <summary>
	/// �X�V�֐��B
	/// </summary>
	void Execute();

	/// <summary>
	/// �{����Delete�ł��B
	/// </summary>
	void ExecuteDeleteGameObjects();


	ShadowMap* GetShadowMap()
	{
		return &m_shadowMap;
	}


	/// <summary>
	/// �}�e���A���ɑ΂��ăN�G�����s���B
	/// </summary>
	/// <param name="func">���₢���킹�֐�</param>
	void QueryMaterials(std::function<void(SkinModel*)> func)
	{
		m_modelDx->UpdateEffects([&](DirectX::IEffect* material) {
			func(reinterpret_cast<SkinModel*>(material));
		});
	}

	/// <summary>
	/// �������擾����B
	/// </summary>
	/// <returns>����</returns>
	Random& GetRandom()
	{
		return m_random;
	}

	/// <summary>
	/// �Q�[���̃^�C�}�[���擾����B
	/// </summary>
	/// <returns>�Q�[���^�C��</returns>
	GameTime& GetGameTime()
	{
		return m_gameTime;
	}

#ifdef _SOUNDENGNE_
	/// <summary>
	/// �T�E���h�G���W�����擾����B
	/// </summary>
	/// <returns>�T�E���h�G���W��</returns>
	SoundEngine& GetSoundEngine()
	{
		return m_soundEngine;
	}
#endif

private:

	DirectX::Model*		m_modelDx;						//!<DirectXTK���񋟂��郂�f���N���X�B

	ShadowMap m_shadowMap;			//�V���h�E�}�b�v�B

	int priorityMax = 32;                           //�D��x�̏���l�B
	int m_currentDeleteObjectBufferNo = 0;			//���݂̍폜�I�u�W�F�N�g�̃o�b�t�@�ԍ��B

	void Start();
	void Update();

	typedef std::list<GameObject*>	GameObjectList;             //���X�g�̐e���B
	std::vector<GameObjectList>	m_gameObjectListArray;			//�Q�[���I�u�W�F�N�g�̗D��x�t�����X�g�B
	GameObjectList	m_deleteObjectArray[2];						//�폜����I�u�W�F�N�g�̃��X�g�B�폜�������s���Ă���Œ���DeleteGameObject���Ă΂��\���������̂ŁA�_�u���o�b�t�@���B

	D3D11_VIEWPORT m_frameBufferViewports;								//�t���[���o�b�t�@�̃r���[�|�[�g�B
	ID3D11RenderTargetView* m_frameBufferRenderTargetView = nullptr;	//�t���[���o�b�t�@�̃����_�����O�^�[�Q�b�g�r���[�B
	ID3D11DepthStencilView* m_frameBufferDepthStencilView = nullptr;	//�t���[���o�b�t�@�̃f�v�X�X�e���V���r���[�B

	RenderTarget m_mainRenderTarget;				//���C�������_�����O�^�[�Q�b�g�B
	Sprite m_copyMainRtToFrameBufferSprite;			//���C�������_�����O�^�[�Q�b�g�ɕ`���ꂽ�G���t���[���o�b�t�@�ɃR�s�[���邽�߂̃X�v���C�g�B
	Random m_random;								//�����_���֐��B
	GameTime m_gameTime;							//�Q�[���^�C���B
#ifdef _SOUNDENGNE_
	SoundEngine m_soundEngine;						//�T�E���h�G���W���B
#endif
};

/// <summary>
/// GameObjectManager�̃C���X�^���X���쐬�B
/// </summary>
/// <returns>�C���X�^���X</returns>
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

/// <summary>
/// �Q�[���I�u�W�F�N�g�̌������ȒP�ɂł���悤�ɂ��邽�߂̊֐��B
/// </summary>
template<class T>
static inline T* FindGO(const char* objectName)
{
	return IGameObjectManager().FindGameObject<T>(objectName);
}

/// <summary>
/// �Q�[���I�u�W�F�N�g���������A��v������̂̃C���X�^���X��n���B
/// </summary>
template<class T>
static inline void QueryGOs(const char* objectName, std::function<bool(T*go)>func)
{
	return IGameObjectManager().FindGameObjects<T>(objectName, func);
}

/// <summary>
/// DleteGOs�pDeleteGO�B
/// </summary>
/// <param name="objectName">�I�u�W�F�N�g�̖��O</param>
static inline void DeleteGO(const char* objectName)
{
	GameObject* go = FindGO<GameObject>(objectName);
	IGameObjectManager().DeleteGameObject(go);
}
#include "GameObject.h"
/// <summary>
/// �Q�[���I�u�W�F�N�g�𖼑O�w��ŏ����B
/// </summary>
/// <param name="objectName">��������Q�[���I�u�W�F�N�g�̖��O</param>
static inline void DeleteGOs(const char* objectName)
{
	
	QueryGOs<GameObject>(objectName, [](auto go) {
		if (go->GetPriority() == 221) {
			int i = 0;
			i++;
		}
		DeleteGO(go);
		return true;
	});
}

/// <summary>
/// �������擾�B
/// </summary>
/// <returns>�����N���X</returns>
static inline Random& random()
{
	return IGameObjectManager().GetRandom();
}

/// <summary>
/// �Q�[���^�C�}�[���擾�B
/// </summary>
/// <returns>�Q�[���^�C�}�[�N���X</returns>
static inline GameTime& gametime()
{
	return IGameObjectManager().GetGameTime();
}

#ifdef _SOUNDENGNE_
/// <summary>
/// �T�E���h�G���W�����擾�B
/// </summary>
/// <returns>�T�E���h�G���W��</returns>
static inline SoundEngine& soundEngine()
{
	return IGameObjectManager().GetSoundEngine();
}
#endif