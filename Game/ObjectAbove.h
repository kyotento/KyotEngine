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
	/// 食べ物をオブジェクトの座標に置く処理。
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
	/// オブジェクトの状態を変更する。
	/// </summary>
	/// <param name="a">状態</param>
	void SetState(int a)
	{
		if (a == 0) {
			m_state = en_default;
		}
		if (a == 1) {
			m_state = en_onObject;
		}
	}

	/// <summary>
	/// オブジェクトの状態を検索する。
	/// </summary>
	/// <returns></returns>
	int GetState()
	{
		return m_state;
	}

protected:

	Belongings* m_belongings = nullptr;
	Gauge* m_gauge = nullptr;

	/// <summary>
	/// オブジェクトの状態。
	/// </summary>
	enum enState
	{
		en_default,					//何も乗っていない状態。
		en_onObject,				//何かオブジェクトが乗ってある状態。

	};

	enState m_state = en_default;

};

