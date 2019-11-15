#pragma once
#include "StageObject.h"
#include "Belongings.h"
#include "Gauge.h"
/// <summary>
/// 物を置くことができるオブジェクトの基底クラス。
/// </summary>

class ObjectAbove : public StageObject
{
public:
	ObjectAbove();
	~ObjectAbove();

	/// <summary>
	/// 持っているものをオブジェクトの座標に置く処理。
	/// </summary>
	/// <param name="">持てるもの</param>
	void PutThings(Belongings*);

	/// <summary>
	/// 乗っているオブジェクトを検索する。
	/// </summary>
	/// <param name="">オブジェクトのポインタの参照</param>
	void TakeThings(Belongings*&);

	/// <summary>
	/// ゲージの座標を指定する。
	/// </summary>
	/// <param name=""></param>
	void SetGaugePosition(Gauge*);

	/// <summary>
	/// オブジェクトの状態。
	/// </summary>
	enum enState
	{
		en_default,					//何も乗っていない状態。
		en_onObject,				//何かオブジェクトが乗ってある状態。

	};

	/// <summary>
	/// オブジェクトの状態を変更する。
	/// </summary>
	/// <param name="objectAboveState">状態</param>
	void SetState(enState objectAboveState)
	{
		m_state = static_cast<enState>(objectAboveState);
	}

	/// <summary>
	/// オブジェクトの状態を検索する。
	/// </summary>
	/// <returns>オブジェクトの状態</returns>
	int GetState()
	{
		return m_state;
	}

protected:

	Belongings* m_belongings = nullptr;			//持つことのできるオブジェクト。
	Gauge* m_gauge = nullptr;					//ゲージ。

	enState m_state = en_default;		//オブジェクトの状態。

};

