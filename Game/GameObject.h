/*!
 *@brief	ゲームオブジェクトの基底クラス。
 */

#pragma once

#define _CGAMEOBJECT_H_

typedef unsigned char GameObjectPriority; //unsigned charの同義語。

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

	//返り値をしっかりと返す。
	virtual bool Start()
	{
		return true;
	}

	//Update関数。
	virtual void Update()
	{

	}

protected:

	GameObjectPriority m_priority;    //実行優先度。
	 
	bool m_startflag;                 //スタートしたか否かのフラグ。
	bool m_deadflag;                  //死亡フラグ。
//	bool m_isRegistDeadList = false;  //僕はね、死亡リストに積まれたかったんだ。
	bool m_activeflag = true;         //アクティブか否かフラグ。

};

