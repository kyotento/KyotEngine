#pragma once
#include "GameObject.h"

class OrderSheet: public GameObject
{
public:
	OrderSheet();
	~OrderSheet();

	bool Start();
	void Update();

	/// <summary>
	/// 座標を指定する関数。
	/// </summary>
	/// <param name="position">座標</param>
	void SetPosition(CVector3 position)
	{
		m_position = position;
	}

	/// <summary>
	/// スケールを指定する関数。
	/// </summary>	
	/// <param name="scale">スケール</param>
	void SetScale(CVector3 scale)
	{
		m_scale = scale;
	}
	/// <summary>
	/// 回転を指定する関数。
	/// </summary>
	/// <param name="rotation">回転</param>
	void SetRotation(CQuaternion rotation)
	{
		m_rotation = rotation;
	}
	/// <summary>
	/// 座標を取得する。
	/// </summary>
	/// <returns>座標</returns>
	CVector3 GetPosition()
	{
		return m_position;
	}

private:

	CVector3 m_position = CVector3::Zero();					//座標。
	CVector3 m_scale = CVector3::One();						//スケール。

	CQuaternion m_rotation = CQuaternion::Identity();		//回転。

	SpriteRender* m_spriteRenderSheetNo1 = nullptr;			//画像生成クラス。一番奥のシート。
	SpriteRender* m_spriteRenderSheetNo2 = nullptr;			//画像生成クラス。手前のシート。

};

