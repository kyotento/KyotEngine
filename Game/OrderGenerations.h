/// <summary>
/// 注文シートの生成処理。
/// </summary>
#pragma once
#include "GameObject.h"
#include "OrderSheet.h"
#include "FoodSheetGenerations.h"

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

	/// <summary>
	/// 料理に使用する食べ物を書くシート。
	/// </summary>
	/// <param name="FoodTypeNum">料理に使用する食べ物の種類</param>
	/// <param name="geneunm">処理している配列の番号</param>
	void FoodSheetGeneration(int FoodTypeNum,int genenum);

	/// <summary>
	/// 生成した食べ物シートの座標更新処理。
	/// </summary>
	void FoodSheetPosUpdate();

private://todo 絶　初期化する。

	static const int m_orderNumLimit = 5;				//注文の上限値。
	int m_orderNumber = 0;								//生成された注文の番号。
	int m_generationNum = 0;							//生成された注文の数。
	float m_sheet_x = 700.f;							//シートのX座標。
	float m_sheet_y = 320.f;							//シートのY座標。
	float m_sheet_z = 0.f;								//シートのZ座標。
	float m_moveLimit[m_orderNumLimit] = { -540.f ,-400.f  ,-260.f  ,-120.f  ,20.f };	//移動上限値。

	float m_orderTimer = 0.f;							//todo 仮　注文が来るタイマー。

	bool m_order = false;								//注文を承ったか否か。
	bool m_foodSheetGenerationFlag = false;				//食べ物シートを生成したか否か。
	
	CVector3 m_position[m_orderNumLimit] = { CVector3::Zero(),CVector3::Zero(),CVector3::Zero(),CVector3::Zero(),CVector3::Zero() };					//座標。
	CVector3 m_scale[m_orderNumLimit] = { CVector3::One() };						//スケール。
	CQuaternion m_rotation[m_orderNumLimit] = { CQuaternion::Identity() };	    	//回転。

	OrderSheet* m_orderSheet[m_orderNumLimit] = {nullptr};			//オーダーシート。
	FoodSheetGenerations* m_foodSheetGenerations = nullptr;			//食べ物のシート。

};

