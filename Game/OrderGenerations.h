/// <summary>
/// 注文シートの生成処理。
/// </summary>
#pragma once
#include "GameObject.h"
#include "OrderSheet.h"
#include "FoodSheetGenerations.h"
#include "CookingList.h"
#include "TimeLimitGauge.h"

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
	/// <param name="genenum">処理している配列の番号</param>
	void FoodSheetPosUpdate(int genenum);

	/// <summary>
	/// その他食べ物と調理方法の画像描画処理。
	/// </summary>
	/// <param name="genenum">処理している配列の番号</param>
	void Order(int genenum);

	/// <summary>
	/// 注文票を消す処理。
	/// </summary>
	/// <param name="genenum">処理している配列の番号</param>
	void DeleteOrder(int genenum);

private://todo 絶　初期化する。

	static const int m_orderNumLimit = 5;				//注文の上限値。

	int m_orderNumber = 0;								//生成された注文の番号。
	int m_generationNum = 0;							//生成された注文の数。
	int m_dishName[m_orderNumLimit] = { 0,0,0,0,0 };	//料理の名前。

	float m_sheet_x = 700.f;							//シートのX座標。
	float m_sheet_y = 330.f;							//シートのY座標。
	float m_sheet_z = 0.f;								//シートのZ座標。
	float m_moveLimit[m_orderNumLimit] = { -540.f ,-400.f  ,-260.f  ,-120.f  ,20.f };	//移動上限値。
	float m_foodPosY[m_orderNumLimit] = { 340.f,340.f,340.f,340.f,340.f};
	float m_foodPosYLimit = 290.f;

	float m_orderTimer = 10.f;							//todo 仮　注文が来るタイマー。

	bool m_order = false;								//注文を承ったか否か。
	bool m_foodSheetGenerationFlag[m_orderNumLimit] = { false };				//食べ物シートを生成したか否か。
	bool m_cuisineSheetFlag[m_orderNumLimit] = { false };			//料理の画像を生成したか否か。
	
	CVector3 m_position[m_orderNumLimit] = { CVector3::Zero(),CVector3::Zero(),CVector3::Zero(),CVector3::Zero(),CVector3::Zero() };					//座標。
	CVector3 m_scale[m_orderNumLimit] = { CVector3::One(),CVector3::One(),CVector3::One(),CVector3::One(),CVector3::One() };							//スケール。
	CVector3 m_foodSheetPosition[m_orderNumLimit] = { CVector3::Zero(),CVector3::Zero(),CVector3::Zero(),CVector3::Zero(),CVector3::Zero() };			//食べ物シートの座標。
	CVector3 m_kitchenWarePosition[m_orderNumLimit] = { CVector3::Zero(),CVector3::Zero() ,CVector3::Zero() ,CVector3::Zero() ,CVector3::Zero() };		//調理器具の画像座標。
	CVector3 m_timeLimitGaugePosition[m_orderNumLimit] = { CVector3::Zero(),CVector3::Zero() ,CVector3::Zero() ,CVector3::Zero() ,CVector3::Zero() };	//タイムリミットゲージの座標。

	CQuaternion m_rotation[m_orderNumLimit] = { CQuaternion::Identity(),CQuaternion::Identity(),CQuaternion::Identity(),CQuaternion::Identity(),CQuaternion::Identity() };	    	//回転。

	OrderSheet* m_orderSheet[m_orderNumLimit] = {nullptr};			//オーダーシート。
	FoodSheetGenerations* m_foodSheetGenerations = nullptr;			//食べ物のシート。
	CookingList* m_cookingList = nullptr;							//料理リスト。
	TimeLimitGauge* m_timeLimitGauge[m_orderNumLimit] = { nullptr };//時間制限ゲージ。

	SpriteRender* m_spriteRenderCuisine[m_orderNumLimit] = { nullptr };					//料理の画像生成用スプライト。	
	SpriteRender* m_spriteRenderFoods[m_orderNumLimit] = { nullptr };					//食べ物の画像生成用スプライト。
	SpriteRender* m_spriteRenderCuisineMethod[m_orderNumLimit] = { nullptr };			//料理の画像生成用スプライト。


};

