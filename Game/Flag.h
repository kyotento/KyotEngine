/// <summary>
/// ステージの旗。
/// </summary>
#pragma once
#include "GameObject.h"

class Flag : public GameObject
{
public:
	Flag();
	~Flag();

	bool Start();
	void Update();

	/// <summary>
	/// ボタンを生成する関数。
	/// </summary>
	void NewButton();

	/// <summary>
	/// ボタンを消す処理。
	/// </summary>
	void DeleteButton();
	
	/// <summary>
	/// 座標を指定する。
	/// </summary>
	/// <param name="pos">座標</param>
	void SetPosition(CVector3 pos)
	{
		m_position = pos;
	}

	/// <summary>
	/// 座標を取得する。
	/// </summary>
	/// <returns>座標</returns>
	CVector3 GetPosition()
	{
		return m_position;
	}

	/// <summary>
	/// スケールを指定する。
	/// </summary>
	/// <param name="scale">スケール</param>
	void SetScale(CVector3 scale)
	{
		m_scale = scale;
	}

	/// <summary>
	/// 回転を指定。
	/// </summary>
	/// <param name="rot">回転</param>
	void SetRotation(CQuaternion rot)
	{
		m_rotation = rot;
	}

private:

	CVector3 m_position = CVector3::Zero();					//座標。
	CVector3 m_position2D = CVector3::Zero();				//画像の座標。
	CVector3 m_scale = CVector3::Zero();					//スケール。
	CVector3 m_scale2D = CVector3::One()*2.f;				//画像のスケール。

	CQuaternion m_rotation = CQuaternion::Identity();		//回転。

	SkinModelRender* m_skinModelRender = nullptr;			//モデル生成。
	SkinModelRender* m_skinModelRenderB = nullptr;			//Bボタン画像生成。


};

