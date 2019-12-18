/// <summary>
/// 注文シートの生成処理。
/// </summary>
#pragma once
#include "GameObject.h"
#include "OrderSheet.h"

class OrderGenerations : public GameObject
{
public:
	OrderGenerations();
	~OrderGenerations();

	bool Start();
	void Update();

	/// <summary>
	/// 生成処理。
	/// </summary>
	void Generations();

	/// <summary>
	/// 移動処理。
	/// </summary>
	void Move();

private://todo 絶　初期化する。

	static const int m_orderNumLimit = 5;				//注文の上限値。
	int m_orderNumber = 0;								//生成された注文の番号。
	int m_generationNum = 0;							//生成された注文の数。
	float m_orderTimer = 0.f;							//todo 仮　注文が来るタイマー。

	bool m_order = false;								//注文を承ったか否か。
	
	CVector3 m_position[m_orderNumLimit] = { CVector3::Zero() };					//座標。
	CVector3 m_scale[m_orderNumLimit] = { CVector3::One() };						//スケール。
	CQuaternion m_rotation[m_orderNumLimit] = { CQuaternion::Identity() };	    	//回転。

	OrderSheet* m_orderSheet[m_orderNumLimit] = {nullptr};			//オーダーシート。

};

