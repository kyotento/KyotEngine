/// <summary>
/// フィールドの基底クラス。
/// </summary>
#pragma once
#include "level/Level.h"
#include "StageObject.h"
#include "Desk.h"
#include "DishHold.h"
#include "GasStove.h"
#include "DustBox.h"
#include "CuttingDesk.h"
#include "Kitchen.h"
#include "Delivery.h"
#include "TomatoBox.h"
#include "OnionBox.h"
#include "Knife.h"
#include "Pot.h"
#include "Belongings.h"
#include "Dish.h"

class Desk;
class DishHold;
class GasStove;
class DustBox;
class CuttingDesk;
class Kitchen;
class Delivery;
class TomatoBox;
class OnionBox;
class Knife;
class StageBase : public GameObject
{
public:
	StageBase();
	~StageBase();

	bool Start();
	void Update();

	/// <summary>
	/// レベル絶対生成するマン。
	/// </summary>
	/// <remarks>
	/// 各オブジェクトの生成処理をする。
	/// 各ステージのレベル生成時に必ず呼ばれる。
	/// </remarks>
//	bool LevelGeneration(LevelObjectData& objData);

protected:

	Level m_level;							//レベル。
	Desk* m_desk = nullptr;					//机。
	DishHold* m_dishHold = nullptr;			//お皿置き。
	GasStove* m_gasStove = nullptr;			//ガスコンロ。
	DustBox* m_dustbox = nullptr;			//ゴミ箱。
	CuttingDesk* m_cuttingDesk = nullptr;	//まな板付き机。
	Kitchen* m_kitchen = nullptr;			//水洗い場。
	Delivery* m_delivery = nullptr;			//受け渡し所。
	TomatoBox* m_tomatoBox = nullptr;		//トマトの箱。
	OnionBox* m_onionBox = nullptr;			//玉ねぎの箱。
	Knife* m_knife = nullptr;				//ナイフ。
	Pot* m_pot = nullptr;					//鍋。
	Belongings* m_belongings = nullptr;		//持つことのできるもの。
	Dish* m_dish = nullptr;					//お皿。

private:

};

