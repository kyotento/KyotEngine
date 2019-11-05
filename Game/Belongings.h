/// <summary>
/// 食べ物の基底クラス。
/// </summary>
#pragma once
#include "StageObject.h"

class Belongings : public StageObject
{
public:
	Belongings();
	~Belongings();

	bool Start();
	void Update();


	void SetState(int a)
	{
		if (a == 0)		//持たれている状態。
		{
			m_state = enHave;		
		}
		if (a == 1)		//置かれている状態。
		{
			m_state = enPutting;
		}
		if (a == 2)		//切られている状態。
		{
			m_state = enCutting;
		}
	}

	/// <summary>
	/// 状態を入手する。
	/// </summary>
	/// <returns>状態</returns>
	int GetState()
	{
		return m_state;
	}

	/// <summary>
	/// 食べ物か調理器具か。
	/// </summary>
	/// <returns>持てるオブジェクトが食べ物か調理器具か判断するための値</returns>
	int GetIndentValue()
	{
		return m_IdentificationValue;
	}


protected:

	/// <summary>
	/// 持てるオブジェクトが食べ物か調理器具か判断するための値。
	/// </summary>
	/// <value>0=食べ物、1=調理器具</value>
	int m_IdentificationValue = 0;			

	/// <summary>	
	/// 食べ物の状態。
	/// </summary>
	enum state
	{
		enHave,				//持たれている状態。
		enPutting,			//置かれている状態。
		enCutting,			//切られている状態。
	};

	state m_state = enPutting;			//食べ物の状態。

private:




};

