#pragma once
#include "Belongings.h"
#include "Cuisine.h"

class Dish : public Belongings
{
public:
	Dish();
	~Dish();

	bool Start();
	void Update();

	/// <summary>
	/// 料理の管理。
	/// </summary>
	void PutDish(int FoodType);

	/// <summary>
	/// 状態変化によるモデルの変更。
	/// </summary>
	void DishModelChange();

	/// <summary>
	///	お皿リストに二つ目以降のお皿を追加する処理。
	/// </summary>
	void AddDishList();

	/// <summary>
	/// お皿リストのお皿を消す処理。
	/// </summary>
	void DeleteDishList(Kitchen* kitchen);

	/// <summary>
	/// お皿の状態。
	/// </summary>
	enum DishState
	{
		endefault,				//きれいなお皿。
		endirty,				//汚れてる。
		enSomethingOnBoard,		//何か乗っているとき。
	};

	/// <summary>
	/// お皿の状態をセットする処理。
	/// </summary>
	/// <param name="dishState">お皿の状態</param>
	void SetDishState(DishState dishState)
	{
		m_dishState = static_cast<DishState>(dishState);
	}

	/// <summary>
	/// お皿の状態を取得する。
	/// </summary>
	/// <returns>お皿の座標</returns>
	int GetState()
	{
		return m_dishState;
	}

	/// <summary>
	/// リストのお皿の数を指定する。
	/// </summary>
	/// <param name="dishListNum"></param>
	void SetDishListNum(int dishListNum)
	{
		m_dishListNum = dishListNum;
	}

	/// <summary>
	/// リストのお皿の数を取得する。
	/// </summary>
	/// <returns>リストのお皿の数</returns>
	int GetDisListNum()
	{
		return m_dishListNum;
	}

private:

	int m_dishListNum = 0;						//リストのお皿の数。

	DishState m_dishState = endefault;			//お皿の状態。
	DishState m_oldDishState = endefault;		//お皿の状態(1フレーム前)。

	Cuisine* m_cuisine = nullptr;				//お料理。
	Kitchen* m_kitchen = nullptr;				//お皿洗い場。


	typedef std::list<SkinModelRender*>DishList;			//お皿を重ねるためのリスト。
	DishList m_dishList;									//お皿リスト。

};

