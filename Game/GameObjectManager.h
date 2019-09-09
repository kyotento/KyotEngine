#pragma once
#define _CGAMEOBJECTMANAGER_H_
#include "GameObject.h"
#include "util/Util.h"
class GameObjectManager /*: public Noncopy*/
{
public:
	/// <summary>
	/// コンストラクタ。
	/// </summary>
	GameObjectManager();

	/// <summary>
	/// デストラクタ。
	/// </summary>
	~GameObjectManager();

	/*
	template <class T>
	
	/// <summary>
	/// NewGO。
	/// </summary>
	/// <param name="m_priority">実行優先度。</param>
	/// <param name=""></param>
	/// <returns></returns>
	T* NewGO(GameObjectPriority m_priority, const wchar_t*)
	{
		T* object = new T();
		m_gameObjectListArray[m_priority].push_back(object);
		return object;
	}
	*/
	//Execute。GOMのアップデートのようなもの。

	/// <summary>
/// インスタンスの取得。
/// </summary>
/// <returns>インスタンス</returns>
	static GameObjectManager& Instance()
	{
		static GameObjectManager instance;
		return instance;
	}



	/// <summary>
	/// ゲームオブジェクトの名前キーを作成。
	/// </summary>
	/// <param name="objectName">オブジェクトの名前</param>
	/// <returns>名前キー</returns>
	static unsigned int MakeGameObjectNameKey(const char* objectName)
	{
		static const unsigned int defaultNameKey = Util::MakeHash("Undefined");	//名前キー。
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
	/// ゲームオブジェクトの追加。
	/// </summary>
	/// <param name="priority">実行優先度</param>
	/// <param name="gameobject">GameObject</param>
	/// <param name="objName">オブジェクトの名前</param>
	/// <remarks>
	/// GameObjectManagerに登録されていなかった場合
	/// {
	///		オブジェクトの名前キーを作成。
	///		優先度付きリストに実行優先度を入れる。
	///		実行優先度の設定。
	///		Startフラグをかえす。
	///		NameKeyを設定する。
	/// }
	/// 死亡フラグがたっていた場合。
	/// {
	///		除外する。
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
	/// ゲームオブジェクトのNew。
	/// </summary>
	/// <param name="priority">ジオ王優先度</param>
	/// <param name="objectName">オブジェクトの名前</param>
	/// <param name="...ctorArgs">可変長引数(コンストラクタに渡す)</param>
	/// <returns>オブジェクト</returns>
	/// <remarks>
	/// Newする。
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
	/// GameObjectの削除。
	/// </summary>
	/// <param name="gameobject">GameObject</param>
	/// <remarks>
	/// GameObjectが存在しているかつ、GameObjectManagerでNEｗされているとき。
	///		死亡フラグを立てる。
	///		GameObjectManagerで追加された。
	///		死亡リストに積まれた。
	///		優先度付きリストに現在の消去オブジェクトを格納。Priorityも。
	///		gameobjectをnullに。
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
	/// 更新関数。
	/// </summary>
	void Execute();

private:

	int priorityMax = 32;                           //優先度の上限値。
	int m_currentDeleteObjectBufferNo = 0;			//現在の削除オブジェクトのバッファ番号。

	void Start();
	void Update();

	typedef std::list<GameObject*>	GameObjectList;                     //リストの親分。
	std::vector<GameObjectList>	m_gameObjectListArray;					//ゲームオブジェクトの優先度付きリスト。
	GameObjectList	m_deleteObjectArray[2];					//削除するオブジェクトのリスト。削除処理を行っている最中にDeleteGameObjectが呼ばれる可能性が高いので、ダブルバッファ化。



	D3D11_VIEWPORT m_frameBufferViewports;								//フレームバッファのビューポート。
	ID3D11RenderTargetView* m_frameBufferRenderTargetView = nullptr;	//フレームバッファのレンダリングターゲットビュー。
	ID3D11DepthStencilView* m_frameBufferDepthStencilView = nullptr;	//フレームバッファのデプスステンシルビュー。

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
/// ゲームオブジェクトの生成を簡単にできるようにするための関数。
/// </summary>
/// <param name="priority">実行優先度</param>
/// <param name="objectName">オブジェクトの名前</param>
/// <param name="...ctorArgs">可変長引数(コンストラクタに渡す)</param>
/// <returns>NewGameObjectの引数</returns>
template<class T, class... TArgs>
static inline T* NewGO(GameObjectPriority priority, const char* objectName, TArgs... ctorArgs)
{
	return IGameObjectManager().NewGameObject<T>((GameObjectPriority)priority, objectName, ctorArgs...);

}


/// <summary>
/// ゲームオブジェクトの削除を簡単にできるようにするための関数。
/// </summary>
/// <param name="go">GAmeObject</param>
static inline void DeleteGO(GameObject* gameobject)
{
	IGameObjectManager().DeleteGameObject(gameobject);
}