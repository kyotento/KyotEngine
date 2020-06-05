/// <summary>
/// 注文シートの食べ物部分を生成するクラス。
/// </summary>
#pragma once
#include "GameObject.h"

class FoodSheetGenerations : public GameObject
{
public:
	FoodSheetGenerations();
	~FoodSheetGenerations();

	bool Start();
	void Update();

	/// <summary>
	/// 料理に使用する食べ物を書くシート。
	/// </summary>
	/// <param name="FoodTypeNum">料理に使う食べ物の種類</param>
	void FoodSheetGeneration(int FoodTypeNum);

	/// <summary>
	/// シートの座標更新。
	/// </summary>
	/// <param name="FoodTypeNum">料理に使う食べ物の種類</param>
	void SheetPos(int FoodTypeNum);

	/// <summary>
	/// 座標のY軸を設定する関数。
	/// </summary>
	/// <param name="Y">Y座標</param>
	void SetPositionY(float Y)
	{
		m_y = Y;
	}

	/// <summary>
	/// 座標設定。
	/// </summary>
	/// <param name="pos">座標</param>
	void SetPosition(CVector3 pos)
	{
		m_position = pos;
	}

private:

	int m_foodNum = 0;
	int m_foodTypeLimit = 4;

	float m_y = 0.f;			//Y座標。
	float m_scaleX = 1.f;		//スケールのY座標。

	bool m_changeScaleFlag = false;

	CVector3 m_position = CVector3::Zero();
	CVector3 m_scale = CVector3::One();
	CQuaternion m_rotation = CQuaternion::Identity();

	SpriteRender* m_spriteRender = nullptr;			//スプライト。


};

