/// <summary>
/// ゲームオブジェクトの基底クラス。
/// </summary>

#pragma once

#define _CGAMEOBJECT_H_

class GameObjectManager;
typedef unsigned char GameObjectPriority; //unsigned charの同義語。ゲームオブジェクトの実行優先度。

class GameObject /*:  Noncopy*/
{

public:
	GameObject() :
		m_priority(0),       //初期優先度０。
		m_startflag(false),  //false。
		m_deadflag(false)    //最初は死んでない。
	{
	}

	virtual ~GameObject();

	/// <summary>
	/// スタート関数。
	/// </summary>
	/// <returns></returns>
	virtual bool Start()
	{
		return true;
	}

	/// <summary>
	/// アップデート関数。
	/// </summary>
	virtual void Update()
	{

	}

	/// <summary>
	/// 
	/// </summary>
	virtual void Render();

	/// <summary>
	/// 死亡フラグを立てる。※エンジン外での実行禁止。
	/// </summary>
	/// <param name="dead">死亡フラグ</param>
	void SetDeadFlag(bool dead)
	{
		m_deadflag = dead;
	}

	/// <summary>
	/// Startしたかどうかを設定する。
	/// </summary>
	/// <param name="start">startflag</param>
	void SetStart(bool start)
	{
		m_startflag = start;
	}

	/// <summary>
	/// 死亡判定。
	/// </summary>
	/// <returns>死亡フラグ。</returns>
	bool IsDead() const
	{
		return m_deadflag;
	}

	/// <summary>
	/// Startしたかどうかを返す。
	/// </summary>
	/// <returns>Startフラグ。</returns>
	virtual bool IsStart() const
	{
		return m_startflag;
	}

	/// <summary>
	/// アクティブ判定。
	/// </summary>
	/// <returns>アクティブフラグ。</returns>
	bool IsActive() const
	{
		return m_activeflag;
	}

	/// <summary>
	/// アクティブフラグの設定。
	/// </summary>
	/// <param name="actflag">アクティブフラグ。</param>
	void SetActiveFlag(bool actflag)
	{
		m_activeflag = actflag;
	}

	/// <summary>
	/// タグの設定。
	/// </summary>
	/// <param name="tag">タグ。</param>
	void SetTag(unsigned int tag)
	{
		m_tags = tag;
	}

	/// <summary>
	/// タグを取得。
	/// </summary>
	/// <returns>タグ。</returns>
	unsigned int GetTag() const
	{
		return m_tags;
	}

	/// <summary>
	/// GameObjectManagerでnewされた。
	/// </summary>
	void SetNewGameObjectManager()
	{
		m_newGameObjectManager = true;
	}

	/// <summary>
	/// GameObjectManagerでnewされたかを返す。
	/// </summary>
	/// <returns>GameObjectMangerでnewされたか。</returns>
	bool GetNewGameObjectManager() const
	{
		return m_newGameObjectManager;
	}

	/// <summary>
	/// m_registrationフラグの設定をする。
	/// </summary>
	/// <param name="reg">GameObjectManagerで追加されたか。</param>
	void SetRegistration(bool reg)
	{
		m_registration = reg;
	}

	/// <summary>
	/// GemObjectManagerで追加されたかを返す。
	/// </summary>
	/// <returns>GAmeObjectMangerで追加されたかフラグ</returns>
	bool GetRegistration() const
	{
		return m_registration;
	}

	/// <summary>
	/// 実行優先度を設定するクラス。
	/// </summary>
	/// <param name="pri">実行優先度。</param>
	void SetPriority(GameObjectPriority pri)
	{
		m_priority = pri;
	}

	/// <summary>
	/// ネームキーを設定する。
	/// </summary>
	/// <param name="snk">名前キー。</param>
	void SetNameKey(unsigned int snk)
	{
		m_nameKey = snk;
	}

	/// <summary>
	/// Renderを使うときのフィルター。
	/// </summary>
	void RenderWrapper()
	{
		if (m_activeflag && m_startflag && m_deadflag && !m_isRegistDeadList)
		{
			Render();
		}
	}

	/// <summary>
	/// アップデートフィルター。
	/// </summary>
	void UpdateWrapper()
	{
		if (m_activeflag && m_startflag && m_deadflag && !m_isRegistDeadList)
		{
			Update();
		}
	}

	/// <summary>
	/// Startを優しく包み込むフィルター。
	/// </summary>
	void StartWrapper()
	{
		if (m_activeflag && m_startflag && m_deadflag && !m_isRegistDeadList) {
			if (Start()) {
				//初期化処理完了。
				m_startflag = true;
			}
		}
	}

protected://派生クラスで使えるよ。

	GameObjectPriority m_priority;    //実行優先度。
	 
	bool m_startflag;                 //スタートしたか否かのフラグ。
	bool m_deadflag;                  //死亡フラグ。
	bool m_isRegistDeadList = false;  //僕はね、死亡リストに積まれたかったんだ。
	bool m_activeflag = true;         //アクティブか否かフラグ。
	bool m_newGameObjectManager;      //ゲームオブジェクトマネージャでnewされたか。
	bool m_registration = false;      //GameObjectManagerで登録されたか(AddGameObjectで使う)。
	unsigned int m_tags = 0;          //タグ。
	unsigned int m_nameKey = 0;	      //名前キー。

};

