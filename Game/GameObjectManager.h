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

	int priorityMax = 32;                            //優先度の上限値。

	typedef std::list<GameObject*>	GameObjectList;                     //リストの親分。
	std::vector<GameObjectList>	m_gameObjectListArray;					//ゲームオブジェクトの優先度付きリスト。

	
};

