/// <summary>
/// 持てるものの基底クラス。
/// </summary>
#pragma once
#include "StageObject.h"

class Kitchen;

class Belongings : public StageObject
{
public:

	Belongings();
	~Belongings();

	bool Start();
	void Update();

	/// <summary>
	/// 状態を入手する。
	/// </summary>
	/// <returns>状態</returns>
	int GetFoodState()
	{
		return m_foodState;
	}

	/// <summary>
	/// 食べ物か調理器具か。
	/// </summary>
	/// <returns>持てるオブジェクトが食べ物か調理器具か判断するための値</returns>
	int GetIndentValue()
	{
		return m_identification;
	}

	/// <summary>
	/// スープっぽいオブジェクトを生成する。
	/// </summary>
	/// <param name="belongings">置いてある持てるもの</param>
	void SetSoupBase(Belongings* puttingBelongings);

	int GetPotFoosType(Belongings* pot);

	void SetPotFoodType(Belongings* pot,int foodType);

	/// <summary>
	/// スープを消す処理。
	/// </summary>
	/// <param name="belongings">置いてある持てるもの</param>
	void DeleteSoup(Belongings* belongings);

	/// <summary>
	///	お皿に食べ物を置く処理。
	/// </summary>
	/// <param name="belongings">持てるもの</param>
	void PutDishs(Belongings* belongings,int FoodType);

	/// <summary>
	/// お皿洗い場の重ねてあるお皿からお皿を一つとる処理。
	/// </summary>
	/// <param name="belongings">持てるもの(お皿)</param>
	/// <param name="Kitchen">お皿洗い場</param>
	void PutDishFromKitchen(Belongings* belongings, Kitchen* kitchen);

	/// <summary>	
	/// 食べ物の状態。
	/// </summary>
	enum state
	{
		enHave,				//持たれている状態。
		enPutting,			//置かれている状態。
		enCutting,			//切られている状態。
	};

	/// <summary>
	/// 食べ物の状態をセットする。
	/// </summary>
	/// <param name="foodsState">食べ物の状態</param>
	void SetState(state foodsState)
	{
		m_foodState = static_cast<state>(foodsState);
	}

	/// <summary>
	/// 食べ物の種類。
	/// </summary>
	enum FoodTypeState
	{
		enTomato,			//トマト。
		enOnion,			//玉ねぎ。
		enFoodTypeNum		//食べ物の種類の数。
	};

	/// <summary>
	/// 食べ物の種類を設定する。
	/// </summary>
	/// <param name="foodTypeState">食べ物の種類</param>
	void SetFoodTypeState(int foodTypeState)
	{
		m_foodTypeState = static_cast<FoodTypeState>(foodTypeState);
	}

	/// <summary>
	/// 食べ物の種類を取得する。
	/// </summary>
	/// <returns>食べ物の種類</returns>
	int GetFoodTypeState()
	{
		return m_foodTypeState;
	}

	/// <summary>
	/// オブジェクトがどの系統に属するか。
	/// </summary>
	enum IdentificationValue
	{
		enFood,				//食べ物。
		enKitchenWare,		//調理器具。
		enDish,				//お皿。
		enDirtyDish			//汚れたお皿。
	};

	/// <summary>
	/// お鍋の状態。
	/// </summary>
	enum PotState
	{
		enZero,			//何も入っていない。
		enOne,			//一つ何かが入っている。
		enTwo,			//ふたつなにかがはいっている。
		enThree,		//三つ何かが入っている状態。
		enComplete		//料理完成。湯で終わっている。
	};

	/// <summary>
	/// お鍋の状態を取得する。
	/// </summary>
	/// <returns>お鍋の状態</returns>
	int GetPotState()
	{
		return m_potState;
	}


protected:		

	bool m_CuttingModel = false;			//切られたモデルになっているか。
														//todo コンストラクタ設定めんどい。
	IdentificationValue m_identification = enFood;		//オブジェクト系統の設定。(各クラスのコンストラクタで設定してあげる必要がある)。

	state m_foodState = enPutting;			//食べ物の状態。

	FoodTypeState m_foodTypeState = enTomato;			//食べ物の種類。

	PotState m_potState = enZero;			//鍋の状態を格納したもの。

private:




};

