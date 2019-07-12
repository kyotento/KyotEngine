/*!
 *@brief	ゲームオブジェクトの基底クラス。
 */

#pragma once

#define _CGAMEOBJECT_H_

class GameObject
{

public:
	GameObject();
	~GameObject();

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


};

