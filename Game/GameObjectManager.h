#pragma once
#define _CGAMEOBJECTMANAGER_H_
//#define _SOUNDENGNE_	//サウンドエンジンを使用するときに定義。
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
	/// ※エラーでここに飛ばされる方へ。
	/// ①　ちゃんと#includeしてる？？。
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
	/// ゲームオブジェクトの検索。(重いよ)。
	/// </summary>
	/// <param name="ObjectName">オブジェクトの名前</param>
	/// <returns>オブジェクト</returns>
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
						//失敗。
					}
					return po;
				}
			}
		}
		//検索に引っかからなかったとき。
		return nullptr;
	}


	/// <summary>
	/// オブジェクトの検索。
	/// </summary>
	/// <param name="objectName">オブジェクトの名前</param>
	/// <param name="funk"></param>
	template<class T>
	void FindGameObjects(const char* objectName, std::function<bool(T*go)> func)
	{
		unsigned int nameKey = Util::MakeHash(objectName);
		for (auto goList : m_gameObjectListArray) {
			for (auto go : goList) {
				if (go->GetNameKey() == nameKey) {
					//見つけた。
					T* p = dynamic_cast<T*>(go);
					if (func(p) == false) {
						//クエリ中断。
						return;
					}
				}
			}
		}
	}


	/// <summary>
	/// フォワードレンダリング描画処理。(通常描画)。
	/// </summary>
	virtual void ForwardRender();


	/// <summary>
	/// レンダリングターゲット切り替え。
	/// </summary>
	/// <param name="d3dDeviceContext">D3Dデバイスコンテキスト</param>
	/// <param name="renderTarget">レンダリングターゲット</param>
	/// <param name="viewport">ビューポート</param>
	void ChangeRenderTarget(ID3D11DeviceContext* d3dDeviceContext, RenderTarget* renderTarget, D3D11_VIEWPORT* viewport);
	void ChangeRenderTarget(ID3D11DeviceContext* d3dDeviceContext, ID3D11RenderTargetView* renderTarget, ID3D11DepthStencilView* depthStensil, D3D11_VIEWPORT* viewport);


	/// <summary>
	/// 更新関数。
	/// </summary>
	void Execute();

	/// <summary>
	/// 本当のDeleteです。
	/// </summary>
	void ExecuteDeleteGameObjects();


	ShadowMap* GetShadowMap()
	{
		return &m_shadowMap;
	}


	/// <summary>
	/// マテリアルに対してクエリを行う。
	/// </summary>
	/// <param name="func">お問い合わせ関数</param>
	void QueryMaterials(std::function<void(SkinModel*)> func)
	{
		m_modelDx->UpdateEffects([&](DirectX::IEffect* material) {
			func(reinterpret_cast<SkinModel*>(material));
		});
	}

	/// <summary>
	/// 乱数を取得する。
	/// </summary>
	/// <returns>乱数</returns>
	Random& GetRandom()
	{
		return m_random;
	}

	/// <summary>
	/// ゲームのタイマーを取得する。
	/// </summary>
	/// <returns>ゲームタイム</returns>
	GameTime& GetGameTime()
	{
		return m_gameTime;
	}

#ifdef _SOUNDENGNE_
	/// <summary>
	/// サウンドエンジンを取得する。
	/// </summary>
	/// <returns>サウンドエンジン</returns>
	SoundEngine& GetSoundEngine()
	{
		return m_soundEngine;
	}
#endif

private:

	DirectX::Model*		m_modelDx;						//!<DirectXTKが提供するモデルクラス。

	ShadowMap m_shadowMap;			//シャドウマップ。

	int priorityMax = 32;                           //優先度の上限値。
	int m_currentDeleteObjectBufferNo = 0;			//現在の削除オブジェクトのバッファ番号。

	void Start();
	void Update();

	typedef std::list<GameObject*>	GameObjectList;             //リストの親分。
	std::vector<GameObjectList>	m_gameObjectListArray;			//ゲームオブジェクトの優先度付きリスト。
	GameObjectList	m_deleteObjectArray[2];						//削除するオブジェクトのリスト。削除処理を行っている最中にDeleteGameObjectが呼ばれる可能性が高いので、ダブルバッファ化。

	D3D11_VIEWPORT m_frameBufferViewports;								//フレームバッファのビューポート。
	ID3D11RenderTargetView* m_frameBufferRenderTargetView = nullptr;	//フレームバッファのレンダリングターゲットビュー。
	ID3D11DepthStencilView* m_frameBufferDepthStencilView = nullptr;	//フレームバッファのデプスステンシルビュー。

	RenderTarget m_mainRenderTarget;				//メインレンダリングターゲット。
	Sprite m_copyMainRtToFrameBufferSprite;			//メインレンダリングターゲットに描かれた絵をフレームバッファにコピーするためのスプライト。
	Random m_random;								//ランダム関数。
	GameTime m_gameTime;							//ゲームタイム。
#ifdef _SOUNDENGNE_
	SoundEngine m_soundEngine;						//サウンドエンジン。
#endif
};

/// <summary>
/// GameObjectManagerのインスタンスを作成。
/// </summary>
/// <returns>インスタンス</returns>
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

/// <summary>
/// ゲームオブジェクトの検索を簡単にできるようにするための関数。
/// </summary>
template<class T>
static inline T* FindGO(const char* objectName)
{
	return IGameObjectManager().FindGameObject<T>(objectName);
}

/// <summary>
/// ゲームオブジェクトを検索し、一致するもののインスタンスを渡す。
/// </summary>
template<class T>
static inline void QueryGOs(const char* objectName, std::function<bool(T*go)>func)
{
	return IGameObjectManager().FindGameObjects<T>(objectName, func);
}

/// <summary>
/// DleteGOs用DeleteGO。
/// </summary>
/// <param name="objectName">オブジェクトの名前</param>
static inline void DeleteGO(const char* objectName)
{
	GameObject* go = FindGO<GameObject>(objectName);
	IGameObjectManager().DeleteGameObject(go);
}
#include "GameObject.h"
/// <summary>
/// ゲームオブジェクトを名前指定で消去。
/// </summary>
/// <param name="objectName">消去するゲームオブジェクトの名前</param>
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
/// 乱数を取得。
/// </summary>
/// <returns>乱数クラス</returns>
static inline Random& random()
{
	return IGameObjectManager().GetRandom();
}

/// <summary>
/// ゲームタイマーを取得。
/// </summary>
/// <returns>ゲームタイマークラス</returns>
static inline GameTime& gametime()
{
	return IGameObjectManager().GetGameTime();
}

#ifdef _SOUNDENGNE_
/// <summary>
/// サウンドエンジンを取得。
/// </summary>
/// <returns>サウンドエンジン</returns>
static inline SoundEngine& soundEngine()
{
	return IGameObjectManager().GetSoundEngine();
}
#endif