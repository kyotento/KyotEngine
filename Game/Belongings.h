/// <summary>
/// 持てるものの基底クラス。
/// </summary>
#pragma once
#include "StageObject.h"
#include "Gauge.h"
#include "Check.h"
#include "CookingList.h"

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

	/// <summary>
	/// お鍋に入っている食べ物の種類を検索する。
	/// </summary>
	/// <param name="pot">検索をかけるお鍋</param>
	/// <returns>お鍋に入っている食べ物の種類</returns>
	int GetPotFoosType(Belongings* pot);

	/// <summary>
	/// お鍋に入っている盛りつける料理を検索。
	/// </summary>
	/// <param name="pot">検索をかけるお鍋</param>
	/// <returns>お鍋に入っている料理</returns>
	int GetGetPotDishCuisine(Belongings* pot);

	/// <summary>
	/// お鍋に入れる食べ物の種類を設定する。
	/// </summary>
	/// <param name="pot">検索をかけるお鍋</param>
	/// <param name="foodType">お鍋に入れる食べ物の種類</param>
	void SetPotFoodType(Belongings* pot,int foodType);

	/// <summary>
	/// スープを消す処理。
	/// </summary>
	/// <param name="belongings">置いてある持てるもの</param>
	void DeleteSoup(Belongings* belongings);

	/// <summary>
	/// お鍋のゲージ拡大処理。
	/// </summary>
	/// <param name="belongings">持てるもの(鍋)</param>
	void PotGaugeExpansion(Belongings* belongings);

	/// <summary>
	///	お皿に食べ物を置く処理。
	/// </summary>
	/// <param name="belongings">持てるもの</param>
	/// <param name="FoodType">食べ物の種類</param>
	void PutDishs(Belongings* belongings,int FoodType);

	/// <summary>
	/// お皿洗い場の重ねてあるお皿からお皿を一つとる処理。
	/// </summary>
	/// <param name="belongings">持てるもの(お皿)</param>
	/// <param name="Kitchen">お皿洗い場</param>
	void PutDishFromKitchen(Belongings* belongings, Kitchen* kitchen);

	/// <summary>
	/// ゲージ生成、拡大、画像差し替えを担う関数。
	/// </summary>
	/// <param name="enlargedDivision">拡大を分割するか</param>
	/// <param name="time">拡大時間</param>
	/// <param name="numberOfTimer">分割回数</param>
	/// <param name="checkGeneration">チェックマークを生成するか</param>
	void GaugeGeneration(bool enlargedDivision, float time, float numberOfTimer = 0.f, bool checkGeneration = true);

	/// <summary>
	/// お皿に載っている料理の状態を設定する。
	/// </summary>
	/// <param name="belongings">お皿</param>
	/// <param name="dishCuisine">料理名</param>
	void SetDishCuisine(Belongings* belongings, int dishCuisine);

	/// <summary>
	/// お皿に載っている料理を取得する。
	/// </summary>
	/// <param name="belongings"></param>
	/// <returns></returns>
	int GetDishCuisine(Belongings* belongings);

	/// <summary>
	/// ゲージの座標更新関数。
	/// </summary>
	void GaugePosUpdate();

	/// <summary>
	/// ゲージを消す処理。
	/// </summary>
	void DeleteGauge();

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

	float m_checkDeleteTimer = 0.f;			//チェックマークを消すタイマー。

	bool m_CuttingModel = false;			//切られたモデルになっているか。
	bool m_GaugeGenerationFlag = false;		//ゲージが生成されたか。

	CVector3 m_gaugePos = CVector3::Zero(); 			//生成されたゲージの座標。
														//todo コンストラクタ設定めんどい。
	IdentificationValue m_identification = enFood;		//オブジェクト系統の設定。(各クラスのコンストラクタで設定してあげる必要がある)。

	state m_foodState = enPutting;			//食べ物の状態。

	FoodTypeState m_foodTypeState = enTomato;			//食べ物の種類。

	PotState m_potState = enZero;			//鍋の状態を格納したもの。

	Gauge* m_gauge = nullptr;
	Check* m_check = nullptr;

private:

};

